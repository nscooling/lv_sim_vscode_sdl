#pragma once

namespace Pinetime {
  namespace Applications {
    class DisplayApp;
    namespace Screens {
      class Screen {
        public:
          explicit Screen(DisplayApp* app) : app{app} {}
          virtual ~Screen() = default;
          virtual bool Refresh() = 0;

          /** @return false if the button hasn't been handled by the app, true if it has been handled */
          virtual bool OnButtonPushed() { return false; }

          /** @return false if the event hasn't been handled by the app, true if it has been handled */
        //   virtual bool OnTouchEvent(TouchEvents event) { return false; }
          virtual bool OnTouchEvent(uint16_t x, uint16_t y) { return false; }

        protected:
          DisplayApp* app;
      };
    }
  }
}