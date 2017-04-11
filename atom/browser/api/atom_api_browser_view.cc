// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_browser_view.h"

#include "atom/browser/api/atom_api_web_contents.h"
#include "atom/browser/browser.h"
#include "atom/browser/native_browser_view.h"
#include "atom/common/color_util.h"
#include "atom/common/native_mate_converters/gfx_converter.h"
#include "atom/common/native_mate_converters/value_converter.h"
#include "atom/common/node_includes.h"
#include "atom/common/options_switches.h"
#include "native_mate/constructor.h"
#include "native_mate/dictionary.h"
#include "ui/gfx/geometry/rect.h"

namespace atom {

namespace api {

BrowserView::BrowserView(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         const mate::Dictionary& options) {
  Init(isolate, wrapper, options);
}

void BrowserView::Init(v8::Isolate* isolate,
                       v8::Local<v8::Object> wrapper,
                       const mate::Dictionary& options) {
  mate::Handle<class api::WebContents> web_contents;
  // If no WebContents was passed to the constructor, create it from options.
  if (!options.Get("webContents", &web_contents)) {
    mate::Dictionary web_preferences = mate::Dictionary::CreateEmpty(isolate);
    options.Get(options::kWebPreferences, &web_preferences);
    web_contents = api::WebContents::Create(isolate, web_preferences);
  }

  web_contents_.Reset(isolate, web_contents.ToV8());

  view_.reset(NativeBrowserView::Create(web_contents.get()));

  InitWith(isolate, wrapper);
}

BrowserView::~BrowserView() {}

// static
mate::WrappableBase* BrowserView::New(mate::Arguments* args) {
  if (!Browser::Get()->is_ready()) {
    args->ThrowError("Cannot create BrowserView before app is ready");
    return nullptr;
  }

  if (args->Length() > 1) {
    args->ThrowError();
    return nullptr;
  }

  mate::Dictionary options;
  if (!(args->Length() == 1 && args->GetNext(&options))) {
    options = mate::Dictionary::CreateEmpty(args->isolate());
  }

  return new BrowserView(args->isolate(), args->GetThis(), options);
}

int32_t BrowserView::ID() const {
  return weak_map_id();
}

void BrowserView::SetBounds(const gfx::Rect& bounds) {
  view_->SetBounds(bounds);
}

void BrowserView::SetBackgroundColor(const std::string& color_name) {
  view_->SetBackgroundColor(ParseHexColor(color_name));
}

v8::Local<v8::Value> BrowserView::WebContents() {
  if (web_contents_.IsEmpty()) {
    return v8::Null(isolate());
  }

  return v8::Local<v8::Value>::New(isolate(), web_contents_);
}

// static
void BrowserView::BuildPrototype(v8::Isolate* isolate,
                                 v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "BrowserView"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("setBounds", &BrowserView::SetBounds)
      .SetMethod("setBackgroundColor", &BrowserView::SetBackgroundColor)
      .SetProperty("webContents", &BrowserView::WebContents)
      .SetProperty("id", &BrowserView::ID);
}

}  // namespace api

}  // namespace atom

namespace {

using atom::api::BrowserView;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  v8::Isolate* isolate = context->GetIsolate();
  BrowserView::SetConstructor(isolate, base::Bind(&BrowserView::New));

  mate::Dictionary browser_view(
      isolate, BrowserView::GetConstructor(isolate)->GetFunction());

  mate::Dictionary dict(isolate, exports);
  dict.Set("BrowserView", browser_view);
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE_BUILTIN(atom_browser_browser_view, Initialize)
