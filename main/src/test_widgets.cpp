#include "test_widgets.h"

#include <memory>
#include <sstream>
#include <utility>

#include "lvgl.h"

static void btn_event_cb(lv_obj_t *btn, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    static uint8_t cnt = 0;
    cnt++;

    /*Get the first child of the button which is the label and change its
     * text*/
    lv_obj_t *label = lv_obj_get_child(btn, nullptr);
    lv_label_set_text_fmt(label, "Button: %d", cnt);
  }
}

#include <string_view>

namespace Lvgl {
using position = std::pair<lv_coord_t, lv_coord_t>;
using size = std::pair<lv_coord_t, lv_coord_t>;

class Label {
public:
  Label() = default;
  Label(position pos, size sz, std::string_view sv);
  Label(lv_obj_t *parent, std::string_view sv);
  explicit Label(lv_obj_t *refernece)
      : label{refernece} {} // convert from raw pointer
  void set_text(std::string_view);

private:
  std::string_view str{};
  lv_obj_t *label{};
};

Label::Label(position pos, size sz, std::string_view sv)
    : str{sv}, label{lv_label_create(lv_scr_act(), nullptr)} {
  auto [x, y] = pos;
  auto [width, height] = sz;
  lv_obj_set_pos(label, x, y);
  lv_obj_set_size(label, width, height);
  lv_label_set_text(label, str.data());
}

Label::Label(lv_obj_t *parent, std::string_view sv)
    : str{sv}, label{lv_label_create(parent, nullptr)} {
  lv_label_set_text(label, str.data());
}

void Label::set_text(std::string_view sv) {
  str = sv;
  lv_label_set_text(label, sv.data());
}

/////////////////////
typedef void (*cb)(lv_obj_t *btn, lv_event_t event);

class Button {
public:
  Button(position pos, size sz);
  Button(position pos, size sz, std::string_view sv);
  Button(lv_obj_t *btn_) : btn{btn_} {}

  void set_callback(cb callback);
  void set_text(std::string_view sv);
  operator lv_obj_t *() { return btn; } // no good practice
  static void set_label_text(lv_obj_t *btn, std::string_view sv);

private:
  lv_obj_t *btn{};
  std::unique_ptr<Label> pLabel{};
};

void Button::set_label_text(lv_obj_t *btn, std::string_view sv) {
  lv_obj_t *label = lv_obj_get_child(btn, nullptr);
  lv_label_set_text_fmt(label, sv.data());
}

Button::Button(position pos, size sz)
    : btn{lv_btn_create(lv_scr_act(), nullptr)} {
  auto [x, y] = pos;
  auto [width, height] = sz;
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height);
}

Button::Button(position pos, size sz, std::string_view sv) : Button{pos, sz} {
  pLabel = std::make_unique<Label>(btn, sv);
}

void Button::set_callback(cb callback) { lv_obj_set_event_cb(btn, callback); }

void Button::set_text(std::string_view sv) { pLabel->set_text(sv); }

class Button_event {
public:
  Button_event(Button &btn) : button{&btn} {}
  void operator()(lv_obj_t *btn, lv_event_t event);

private:
  Button *button;
};

void Button_event::operator()(lv_obj_t *btn, lv_event_t event) {
  button->set_text("pressed");
}

} // namespace Lvgl

void exec() {
  Lvgl::Label label{{10, 70}, {120, 100}, "Hello"};
  Lvgl::Button button{{10, 10}, {120, 50}, "Button"};

  button.set_callback([](auto btn, auto event) {
    if (event == LV_EVENT_CLICKED) {
      static unsigned cnt{};
      std::string str{"Button: "};
      str += std::to_string(++cnt);
      Lvgl::Button::set_label_text(btn, str.c_str());
    }
  });
}
