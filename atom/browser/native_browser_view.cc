// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/native_browser_view.h"

#include "atom/browser/api/atom_api_web_contents.h"
#include "brightray/browser/inspectable_web_contents_view.h"

namespace atom {

NativeBrowserView::NativeBrowserView(const api::WebContents* web_contents)
    : api_web_contents_(web_contents) {}

NativeBrowserView::~NativeBrowserView() {}

brightray::InspectableWebContentsView*
NativeBrowserView::GetInspectableWebContentsView() {
  return api_web_contents_->managed_web_contents()->GetView();
}

}  // namespace atom
