// Copyright 2015 The Chromium Embedded Framework Authors.
// Portions copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_EXTENSIONS_EXTENSIONS_BROWSER_CLIENT_H_
#define CEF_LIBCEF_BROWSER_EXTENSIONS_EXTENSIONS_BROWSER_CLIENT_H_

#include "libcef/browser/extensions/event_router_forwarder.h"

#include "base/compiler_specific.h"
#include "extensions/browser/extensions_browser_client.h"

namespace extensions {

class ExtensionsAPIClient;

// An ExtensionsBrowserClient that supports a single content::BrowserContent
// with no related incognito context.
class CefExtensionsBrowserClient : public ExtensionsBrowserClient {
 public:
  CefExtensionsBrowserClient();
  ~CefExtensionsBrowserClient() override;

  // ExtensionsBrowserClient overrides:
  bool IsShuttingDown() override;
  bool AreExtensionsDisabled(const base::CommandLine& command_line,
                             content::BrowserContext* context) override;
  bool IsValidContext(content::BrowserContext* context) override;
  bool IsSameContext(content::BrowserContext* first,
                     content::BrowserContext* second) override;
  bool HasOffTheRecordContext(content::BrowserContext* context) override;
  content::BrowserContext* GetOffTheRecordContext(
      content::BrowserContext* context) override;
  content::BrowserContext* GetOriginalContext(
      content::BrowserContext* context) override;
  bool IsGuestSession(content::BrowserContext* context) const override;
  bool IsExtensionIncognitoEnabled(
      const std::string& extension_id,
      content::BrowserContext* context) const override;
  bool CanExtensionCrossIncognito(
      const Extension* extension,
      content::BrowserContext* context) const override;
  net::URLRequestJob* MaybeCreateResourceBundleRequestJob(
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate,
      const base::FilePath& directory_path,
      const std::string& content_security_policy,
      bool send_cors_header) override;
  bool AllowCrossRendererResourceLoad(net::URLRequest* request,
                                      bool is_incognito,
                                      const Extension* extension,
                                      InfoMap* extension_info_map) override;
  PrefService* GetPrefServiceForContext(
      content::BrowserContext* context) override;
  void GetEarlyExtensionPrefsObservers(
      content::BrowserContext* context,
      std::vector<ExtensionPrefsObserver*>* observers) const
      override;
  ProcessManagerDelegate* GetProcessManagerDelegate() const override;
  scoped_ptr<ExtensionHostDelegate>
  CreateExtensionHostDelegate() override;
  bool DidVersionUpdate(content::BrowserContext* context) override;
  void PermitExternalProtocolHandler() override;
  scoped_ptr<AppSorting> CreateAppSorting() override;
  bool IsRunningInForcedAppMode() override;
  ApiActivityMonitor* GetApiActivityMonitor(
      content::BrowserContext* context) override;
  ExtensionSystemProvider* GetExtensionSystemFactory() override;
  void RegisterExtensionFunctions(
      ExtensionFunctionRegistry* registry) const override;
  void RegisterMojoServices(content::RenderFrameHost* render_frame_host,
                            const Extension* extension) const override;
  scoped_ptr<RuntimeAPIDelegate> CreateRuntimeAPIDelegate(
      content::BrowserContext* context) const override;
  const ComponentExtensionResourceManager*
  GetComponentExtensionResourceManager() override;
  void BroadcastEventToRenderers(const std::string& event_name,
                                 scoped_ptr<base::ListValue> args) override;
  net::NetLog* GetNetLog() override;
  ExtensionCache* GetExtensionCache() override;
  bool IsBackgroundUpdateAllowed() override;
  bool IsMinBrowserVersionSupported(const std::string& min_version) override;
  ExtensionWebContentsObserver* GetExtensionWebContentsObserver(
      content::WebContents* web_contents) override;

  // Sets the API client.
  void SetAPIClientForTest(ExtensionsAPIClient* api_client);

 private:
  // Support for extension APIs.
  scoped_ptr<ExtensionsAPIClient> api_client_;

  // Resource manager used to supply resources from pak files.
  scoped_ptr<ComponentExtensionResourceManager> resource_manager_;

  scoped_refptr<EventRouterForwarder> event_router_forwarder_;

  DISALLOW_COPY_AND_ASSIGN(CefExtensionsBrowserClient);
};

}  // namespace extensions

#endif  // CEF_LIBCEF_BROWSER_EXTENSIONS_EXTENSIONS_BROWSER_CLIENT_H_
