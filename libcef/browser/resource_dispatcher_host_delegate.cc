// Copyright 2015 The Chromium Embedded Framework Authors.
// Portions copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/resource_dispatcher_host_delegate.h"
#include "libcef/browser/browser_host_impl.h"
#include "libcef/browser/extensions/api/streams_private/streams_private_api.h"
#include "libcef/browser/origin_whitelist_impl.h"
#include "libcef/browser/resource_context.h"
#include "libcef/browser/thread_util.h"
#include "libcef/common/request_impl.h"
#include "libcef/common/extensions/extensions_util.h"

#include "base/guid.h"
#include "base/memory/scoped_vector.h"
#include "components/navigation_interception/intercept_navigation_resource_throttle.h"
#include "components/navigation_interception/navigation_params.h"
#include "content/public/browser/plugin_service.h"
#include "content/public/browser/plugin_service_filter.h"
#include "content/public/browser/resource_request_info.h"
#include "content/public/browser/stream_info.h"
#include "content/public/common/resource_response.h"
#include "content/public/common/webplugininfo.h"
#include "extensions/common/constants.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest_handlers/mime_types_handler.h"
#include "net/http/http_response_headers.h"
#include "net/url_request/url_request.h"

namespace {

bool NavigationOnUIThread(
    int64 frame_id,
    CefRefPtr<CefRequestImpl> request,
    content::WebContents* source,
    const navigation_interception::NavigationParams& params) {
  CEF_REQUIRE_UIT();

  bool ignore_navigation = false;

  CefRefPtr<CefBrowserHostImpl> browser =
      CefBrowserHostImpl::GetBrowserForContents(source);
  if (browser.get()) {
    CefRefPtr<CefClient> client = browser->GetClient();
    if (client.get()) {
      CefRefPtr<CefRequestHandler> handler = client->GetRequestHandler();
      if (handler.get()) {
        CefRefPtr<CefFrame> frame;
        if (frame_id >= 0)
          frame = browser->GetFrame(frame_id);
        DCHECK(frame.get());
        if (frame.get()) {
          ignore_navigation = handler->OnBeforeBrowse(
              browser.get(), frame, request.get(), params.is_redirect());
        }
      }
    }
  }

  return ignore_navigation;
}

// TODO(raymes): This won't return the right result if plugins haven't been
// loaded yet. Fixing this properly really requires fixing crbug.com/443466.
bool IsPluginEnabledForExtension(const extensions::Extension* extension,
                                 const content::ResourceRequestInfo* info,
                                 const std::string& mime_type,
                                 const GURL& url) {
  content::PluginService* service = content::PluginService::GetInstance();
  std::vector<content::WebPluginInfo> plugins;
  service->GetPluginInfoArray(url, mime_type, true, &plugins, nullptr);
  content::PluginServiceFilter* filter = service->GetFilter();

  for (auto& plugin : plugins) {
    // Check that the plugin is running the extension.
    if (plugin.path !=
        base::FilePath::FromUTF8Unsafe(extension->url().spec())) {
      continue;
    }
    // Check that the plugin is actually enabled.
    if (!filter || filter->IsPluginAvailable(info->GetChildID(),
                                             info->GetRenderFrameID(),
                                             info->GetContext(),
                                             url,
                                             GURL(),
                                             &plugin)) {
      return true;
    }
  }
  return false;
}

void SendExecuteMimeTypeHandlerEvent(scoped_ptr<content::StreamInfo> stream,
                                     int64 expected_content_size,
                                     int render_process_id,
                                     int render_frame_id,
                                     const std::string& extension_id,
                                     const std::string& view_id,
                                     bool embedded) {
  CEF_REQUIRE_UIT();

  CefRefPtr<CefBrowserHostImpl> browser =
      CefBrowserHostImpl::GetBrowserForFrame(render_process_id,
                                             render_frame_id);
  if (!browser.get())
    return;

  content::WebContents* web_contents = browser->web_contents();
  if (!web_contents)
    return;

  content::BrowserContext* browser_context = web_contents->GetBrowserContext();

  extensions::StreamsPrivateAPI* streams_private =
      extensions::StreamsPrivateAPI::Get(browser_context);
  if (!streams_private)
    return;

  // A |tab_id| value of -1 disables zoom management in the PDF extension.
  // Otherwise we need to implement chrome.tabs zoom handling. See
  // chrome/browser/resources/pdf/browser_api.js.
  int tab_id = -1;

  streams_private->ExecuteMimeTypeHandler(
      extension_id, tab_id, stream.Pass(), view_id, expected_content_size,
      embedded, render_process_id, render_frame_id);
}

}  // namespace

CefResourceDispatcherHostDelegate::CefResourceDispatcherHostDelegate() {
}

CefResourceDispatcherHostDelegate::~CefResourceDispatcherHostDelegate() {
}

void CefResourceDispatcherHostDelegate::RequestBeginning(
    net::URLRequest* request,
    content::ResourceContext* resource_context,
    content::AppCacheService* appcache_service,
    content::ResourceType resource_type,
    ScopedVector<content::ResourceThrottle>* throttles) {
  if (resource_type == content::ResourceType::RESOURCE_TYPE_MAIN_FRAME ||
      resource_type == content::ResourceType::RESOURCE_TYPE_SUB_FRAME) {
    int64 frame_id = -1;

    // ResourceRequestInfo will not exist for requests originating from
    // WebURLLoader in the render process.
    const content::ResourceRequestInfo* info =
        content::ResourceRequestInfo::ForRequest(request);
    if (info)
      frame_id = info->GetRenderFrameID();

    if (frame_id >= 0) {
      CefRefPtr<CefRequestImpl> cef_request(new CefRequestImpl);
      cef_request->Set(request);
      cef_request->SetReadOnly(true);

      content::ResourceThrottle* throttle =
        new navigation_interception::InterceptNavigationResourceThrottle(
            request,
            base::Bind(&NavigationOnUIThread, frame_id, cef_request));
      throttles->push_back(throttle);
    }
  }
}

bool CefResourceDispatcherHostDelegate::HandleExternalProtocol(
    const GURL& url,
    int child_id,
    int route_id,
    bool is_main_frame,
    ui::PageTransition page_transition,
    bool has_user_gesture) {
  CefRefPtr<CefBrowserHostImpl> browser =
      CefBrowserHostImpl::GetBrowserForView(child_id, route_id);
  if (browser.get())
    browser->HandleExternalProtocol(url);
  return false;
}

// Implementation based on
// ChromeResourceDispatcherHostDelegate::ShouldInterceptResourceAsStream.
bool CefResourceDispatcherHostDelegate::ShouldInterceptResourceAsStream(
    net::URLRequest* request,
    const std::string& mime_type,
    GURL* origin,
    std::string* payload) {
  if (!extensions::ExtensionsEnabled())
    return false;

  const content::ResourceRequestInfo* info =
      content::ResourceRequestInfo::ForRequest(request);
  CefResourceContext* context =
      static_cast<CefResourceContext*>(info->GetContext());
  bool profile_is_off_the_record = context->IsOffTheRecord();
  const scoped_refptr<const extensions::InfoMap> extension_info_map(
      context->GetExtensionInfoMap());

  std::vector<std::string> whitelist = MimeTypesHandler::GetMIMETypeWhitelist();
  // Go through the white-listed extensions and try to use them to intercept
  // the URL request.
  for (const std::string& extension_id : whitelist) {
    const extensions::Extension* extension =
        extension_info_map->extensions().GetByID(extension_id);
    // The white-listed extension may not be installed, so we have to NULL check
    // |extension|.
    if (!extension ||
        (profile_is_off_the_record &&
         !extension_info_map->IsIncognitoEnabled(extension_id))) {
      continue;
    }

    MimeTypesHandler* handler = MimeTypesHandler::GetHandler(extension);
    if (handler && handler->CanHandleMIMEType(mime_type)) {
      StreamTargetInfo target_info;
      *origin = extensions::Extension::GetBaseURLFromExtensionId(extension_id);
      target_info.extension_id = extension_id;
      if (!handler->handler_url().empty()) {
        // This is reached in the case of MimeHandlerViews. If the
        // MimeHandlerView plugin is disabled, then we shouldn't intercept the
        // stream.
        if (!IsPluginEnabledForExtension(extension, info, mime_type,
                                         request->url())) {
          continue;
        }
        target_info.view_id = base::GenerateGUID();
        *payload = target_info.view_id;
      }
      stream_target_info_[request] = target_info;
      return true;
    }
  }

  return false;
}

// Implementation based on
// ChromeResourceDispatcherHostDelegate::OnStreamCreated.
void CefResourceDispatcherHostDelegate::OnStreamCreated(
    net::URLRequest* request,
    scoped_ptr<content::StreamInfo> stream) {
  DCHECK(extensions::ExtensionsEnabled());
  const content::ResourceRequestInfo* info =
      content::ResourceRequestInfo::ForRequest(request);
  std::map<net::URLRequest*, StreamTargetInfo>::iterator ix =
      stream_target_info_.find(request);
  CHECK(ix != stream_target_info_.end());
  bool embedded = info->GetResourceType() != content::RESOURCE_TYPE_MAIN_FRAME;
  CEF_POST_TASK(CEF_UIT,
      base::Bind(&SendExecuteMimeTypeHandlerEvent, base::Passed(&stream),
                 request->GetExpectedContentSize(), info->GetChildID(),
                 info->GetRenderFrameID(), ix->second.extension_id,
                 ix->second.view_id, embedded));
  stream_target_info_.erase(request);
}

void CefResourceDispatcherHostDelegate::OnRequestRedirected(
    const GURL& redirect_url,
    net::URLRequest* request,
    content::ResourceContext* resource_context,
    content::ResourceResponse* response) {
  const GURL& active_url = request->url();
  if (active_url.is_valid() && redirect_url.is_valid() &&
      active_url.GetOrigin() != redirect_url.GetOrigin() &&
      HasCrossOriginWhitelistEntry(active_url, redirect_url)) {
    if (!response->head.headers.get())
      response->head.headers = new net::HttpResponseHeaders(std::string());

    // Add CORS headers to support XMLHttpRequest redirects.
    response->head.headers->AddHeader("Access-Control-Allow-Origin: " +
        active_url.scheme() + "://" + active_url.host());
    response->head.headers->AddHeader("Access-Control-Allow-Credentials: true");
  }
}
