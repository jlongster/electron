// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_NATIVE_BROWSER_VIEW_VIEWS_H_
#define ATOM_BROWSER_NATIVE_BROWSER_VIEW_VIEWS_H_

#include "atom/browser/native_browser_view.h"

namespace atom {

class NativeBrowserViewViews : public NativeBrowserView {
 public:
  explicit NativeBrowserViewViews(const api::WebContents* web_contents);
  ~NativeBrowserViewViews() override;

  void SetBounds(const gfx::Rect& bounds) override;
  void SetBackgroundColor(SkColor color) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(NativeBrowserViewViews);
};

}  // namespace atom

#endif  // ATOM_BROWSER_NATIVE_BROWSER_VIEW_VIEWS_H_
