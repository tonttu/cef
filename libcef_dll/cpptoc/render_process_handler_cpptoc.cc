// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/load_handler_cpptoc.h"
#include "libcef_dll/cpptoc/render_process_handler_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/domnode_ctocpp.h"
#include "libcef_dll/ctocpp/frame_ctocpp.h"
#include "libcef_dll/ctocpp/list_value_ctocpp.h"
#include "libcef_dll/ctocpp/process_message_ctocpp.h"
#include "libcef_dll/ctocpp/request_ctocpp.h"
#include "libcef_dll/ctocpp/v8context_ctocpp.h"
#include "libcef_dll/ctocpp/v8exception_ctocpp.h"
#include "libcef_dll/ctocpp/v8stack_trace_ctocpp.h"


namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK render_process_handler_on_render_thread_created(
    struct _cef_render_process_handler_t* self,
    struct _cef_list_value_t* extra_info) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: extra_info; type: refptr_diff
  DCHECK(extra_info);
  if (!extra_info)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnRenderThreadCreated(
      CefListValueCToCpp::Wrap(extra_info));
}

void CEF_CALLBACK render_process_handler_on_web_kit_initialized(
    struct _cef_render_process_handler_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnWebKitInitialized();
}

void CEF_CALLBACK render_process_handler_on_browser_created(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnBrowserCreated(
      CefBrowserCToCpp::Wrap(browser));
}

void CEF_CALLBACK render_process_handler_on_browser_destroyed(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnBrowserDestroyed(
      CefBrowserCToCpp::Wrap(browser));
}

cef_load_handler_t* CEF_CALLBACK render_process_handler_get_load_handler(
    struct _cef_render_process_handler_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefLoadHandler> _retval = CefRenderProcessHandlerCppToC::Get(
      self)->GetLoadHandler();

  // Return type: refptr_same
  return CefLoadHandlerCppToC::Wrap(_retval);
}

int CEF_CALLBACK render_process_handler_on_before_navigation(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_frame_t* frame, struct _cef_request_t* request,
    cef_navigation_type_t navigation_type, int is_redirect) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return 0;
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame)
    return 0;
  // Verify param: request; type: refptr_diff
  DCHECK(request);
  if (!request)
    return 0;

  // Execute
  bool _retval = CefRenderProcessHandlerCppToC::Get(self)->OnBeforeNavigation(
      CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame),
      CefRequestCToCpp::Wrap(request),
      navigation_type,
      is_redirect?true:false);

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK render_process_handler_on_context_created(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_frame_t* frame, struct _cef_v8context_t* context) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame)
    return;
  // Verify param: context; type: refptr_diff
  DCHECK(context);
  if (!context)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnContextCreated(
      CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame),
      CefV8ContextCToCpp::Wrap(context));
}

void CEF_CALLBACK render_process_handler_on_context_released(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_frame_t* frame, struct _cef_v8context_t* context) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame)
    return;
  // Verify param: context; type: refptr_diff
  DCHECK(context);
  if (!context)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnContextReleased(
      CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame),
      CefV8ContextCToCpp::Wrap(context));
}

void CEF_CALLBACK render_process_handler_on_uncaught_exception(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_frame_t* frame, struct _cef_v8context_t* context,
    struct _cef_v8exception_t* exception,
    struct _cef_v8stack_trace_t* stackTrace) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: frame; type: refptr_diff
  DCHECK(frame);
  if (!frame)
    return;
  // Verify param: context; type: refptr_diff
  DCHECK(context);
  if (!context)
    return;
  // Verify param: exception; type: refptr_diff
  DCHECK(exception);
  if (!exception)
    return;
  // Verify param: stackTrace; type: refptr_diff
  DCHECK(stackTrace);
  if (!stackTrace)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnUncaughtException(
      CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame),
      CefV8ContextCToCpp::Wrap(context),
      CefV8ExceptionCToCpp::Wrap(exception),
      CefV8StackTraceCToCpp::Wrap(stackTrace));
}

void CEF_CALLBACK render_process_handler_on_focused_node_changed(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_frame_t* frame, cef_domnode_t* node, const cef_rect_t* nodeBounds) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: nodeBounds; type: simple_byref_const
  DCHECK(nodeBounds);
  if (!nodeBounds)
    return;
  // Unverified params: frame, node

  // Translate param: nodeBounds; type: simple_byref_const
  CefRect nodeBoundsVal = nodeBounds?*nodeBounds:CefRect();

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnFocusedNodeChanged(
      CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame),
      CefDOMNodeCToCpp::Wrap(node),
      nodeBoundsVal);
}

void CEF_CALLBACK render_process_handler_on_editable_node_touched(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser, int x,
    int y) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;

  // Execute
  CefRenderProcessHandlerCppToC::Get(self)->OnEditableNodeTouched(
      CefBrowserCToCpp::Wrap(browser),
      x,
      y);
}

int CEF_CALLBACK render_process_handler_on_process_message_received(
    struct _cef_render_process_handler_t* self, cef_browser_t* browser,
    cef_process_id_t source_process, cef_process_message_t* message) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return 0;
  // Verify param: message; type: refptr_diff
  DCHECK(message);
  if (!message)
    return 0;

  // Execute
  bool _retval = CefRenderProcessHandlerCppToC::Get(
      self)->OnProcessMessageReceived(
      CefBrowserCToCpp::Wrap(browser),
      source_process,
      CefProcessMessageCToCpp::Wrap(message));

  // Return type: bool
  return _retval;
}

}  // namespace


// CONSTRUCTOR - Do not edit by hand.

CefRenderProcessHandlerCppToC::CefRenderProcessHandlerCppToC() {
  GetStruct()->on_render_thread_created =
      render_process_handler_on_render_thread_created;
  GetStruct()->on_web_kit_initialized =
      render_process_handler_on_web_kit_initialized;
  GetStruct()->on_browser_created = render_process_handler_on_browser_created;
  GetStruct()->on_browser_destroyed =
      render_process_handler_on_browser_destroyed;
  GetStruct()->get_load_handler = render_process_handler_get_load_handler;
  GetStruct()->on_before_navigation =
      render_process_handler_on_before_navigation;
  GetStruct()->on_context_created = render_process_handler_on_context_created;
  GetStruct()->on_context_released = render_process_handler_on_context_released;
  GetStruct()->on_uncaught_exception =
      render_process_handler_on_uncaught_exception;
  GetStruct()->on_focused_node_changed =
      render_process_handler_on_focused_node_changed;
  GetStruct()->on_editable_node_touched =
      render_process_handler_on_editable_node_touched;
  GetStruct()->on_process_message_received =
      render_process_handler_on_process_message_received;
}

template<> CefRefPtr<CefRenderProcessHandler> CefCppToC<CefRenderProcessHandlerCppToC,
    CefRenderProcessHandler, cef_render_process_handler_t>::UnwrapDerived(
    CefWrapperType type, cef_render_process_handler_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCppToC<CefRenderProcessHandlerCppToC,
    CefRenderProcessHandler, cef_render_process_handler_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCppToC<CefRenderProcessHandlerCppToC,
    CefRenderProcessHandler, cef_render_process_handler_t>::kWrapperType =
    WT_RENDER_PROCESS_HANDLER;
