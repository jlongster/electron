// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_NATIVE_BROWSER_VIEW_H_
#define ATOM_BROWSER_NATIVE_BROWSER_VIEW_H_

#include "base/macros.h"
#include "third_party/skia/include/core/SkColor.h"

namespace brightray {
class InspectableWebContentsView;
}

namespace gfx {
class Rect;
}

namespace atom {

namespace api {
class WebContents;
}

class NativeBrowserView {
 public:
  virtual ~NativeBrowserView();

  static NativeBrowserView* Create(const api::WebContents* web_contents);

  brightray::InspectableWebContentsView* GetInspectableWebContentsView();
  const api::WebContents* GetWebContents() { return api_web_contents_; }

  virtual void SetBounds(const gfx::Rect& bounds) = 0;
  virtual void SetBackgroundColor(SkColor color) = 0;

 protected:
  explicit NativeBrowserView(const api::WebContents* web_contents);

  const api::WebContents* api_web_contents_;

 private:
  DISALLOW_COPY_AND_ASSIGN(NativeBrowserView);
};

}  // namespace atom

#endif  // ATOM_BROWSER_NATIVE_BROWSER_VIEW_H_
