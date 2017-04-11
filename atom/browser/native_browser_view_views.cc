// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/native_browser_view_views.h"

#include "brightray/browser/inspectable_web_contents_view.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/views/background.h"

namespace atom {

NativeBrowserViewViews::NativeBrowserViewViews(
    const api::WebContents* web_contents)
    : NativeBrowserView(web_contents) {}

NativeBrowserViewViews::~NativeBrowserViewViews() {}

void NativeBrowserViewViews::SetBounds(const gfx::Rect& bounds) {
  auto* view = GetInspectableWebContentsView()->GetView();
  view->SetBoundsRect(bounds);
}

void NativeBrowserViewViews::SetBackgroundColor(SkColor color) {
  auto* view = GetInspectableWebContentsView()->GetView();
  view->set_background(views::Background::CreateSolidBackground(color));
}

// static
NativeBrowserView* NativeBrowserView::Create(
    const api::WebContents* web_contents) {
  return new NativeBrowserViewViews(web_contents);
}

}  // namespace atom
