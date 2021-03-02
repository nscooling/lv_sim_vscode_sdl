
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <unistd.h>
#include <cstdio>

#include "hal_init.h"
// #include "lv_examples/lv_examples.h"
#include "lvgl/lvgl.h"
#include "src/lv_core/lv_obj.h"
#include "src/lv_misc/lv_area.h"
// #include "test_widgets.h"

// LV_ALIGN_...
static lv_obj_t * lv_ex_label_1(const char* str, lv_label_align_t align)
{
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_align(label1, LV_LABEL_ALIGN_LEFT);      // lv_label_set_align(label, LV_LABEL_ALIGN_LEFT/RIGHT/CENTER). 
    lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label1, str);
    lv_obj_set_width(label1, 150);
    lv_obj_align(label1, nullptr, align, 0, 0); // lv_obj_align(obj, obj_ref, LV_ALIGN_..., x_ofs, y_ofs).
    return label1;
}

static void lv_ex_label_relative(lv_obj_t * label, const char* str, lv_label_align_t align, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_align(label1, LV_LABEL_ALIGN_LEFT);      // lv_label_set_align(label, LV_LABEL_ALIGN_LEFT/RIGHT/CENTER). 
    lv_label_set_text(label1, str);

    lv_obj_set_width(label1, 150);
    lv_obj_align(label1, label, align, x, y); // lv_obj_align(obj, obj_ref, LV_ALIGN_..., x_ofs, y_ofs).
}

void display_labels()
{
  auto label1 = lv_ex_label_1("#0000ff " "Centre" " #", LV_ALIGN_CENTER);       // 0
  // auto label1 = lv_ex_label_1("Centre", LV_ALIGN_CENTER);       // 0

  lv_ex_label_1("T-L", LV_ALIGN_IN_TOP_LEFT);     // 1  0001
  lv_ex_label_1("T-M", LV_ALIGN_IN_TOP_MID);      // 2  0010
  lv_ex_label_1("T-R", LV_ALIGN_IN_TOP_RIGHT);    // 3  0011

  lv_ex_label_1("B-L", LV_ALIGN_IN_BOTTOM_LEFT);  // 4  0100
  lv_ex_label_1("B-M", LV_ALIGN_IN_BOTTOM_MID);   // 5  0101
  lv_ex_label_1("B-R", LV_ALIGN_IN_BOTTOM_RIGHT); // 6  0110

  lv_ex_label_1("M-L", LV_ALIGN_IN_LEFT_MID);     // 7  0111
  lv_ex_label_1("M-R", LV_ALIGN_IN_RIGHT_MID);    // 8  1000


  lv_ex_label_relative(label1, "T-L", LV_ALIGN_OUT_TOP_LEFT, -20,-20);     // 1  0001
  lv_ex_label_relative(label1, "T-M", LV_ALIGN_OUT_TOP_MID, 0, -20);      // 2  0020
  lv_ex_label_relative(label1, "T-R", LV_ALIGN_OUT_TOP_RIGHT, 20,-20);    // 3  0011

  lv_ex_label_relative(label1, "B-L", LV_ALIGN_OUT_BOTTOM_LEFT,-20,20);  // 4  0200
  lv_ex_label_relative(label1, "B-M", LV_ALIGN_OUT_BOTTOM_MID,0,20);   // 5  0201
  lv_ex_label_relative(label1, "B-R", LV_ALIGN_OUT_BOTTOM_RIGHT, 20,20); // 6  0120

  lv_ex_label_relative(label1, "M-L", LV_ALIGN_OUT_LEFT_MID,-20,0);     // 7  0111
  lv_ex_label_relative(label1, "M-R", LV_ALIGN_OUT_RIGHT_MID,20,0);    // 8  1000

  // lv_obj_set_hidden(label1, true);
}




static lv_obj_t * led1{};
void button_led_example()
{
  auto event_handler = [](lv_obj_t * obj, lv_event_t event)
  {
        if(event == LV_EVENT_CLICKED) {
            printf("Clicked\n");
            lv_led_toggle(led1);
        }
        else if(event == LV_EVENT_VALUE_CHANGED) {
            printf("Toggled\n");
        }
    };

      /*Create a LED and switch it OFF*/
    // lv_obj_t * led1  = lv_led_create(lv_scr_act(), nullptr);
    led1  = lv_led_create(lv_scr_act(), nullptr);
    lv_obj_align(led1, nullptr, LV_ALIGN_CENTER, 0, 0);
    lv_led_off(led1);

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), nullptr);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, nullptr, LV_ALIGN_IN_TOP_MID, 0, 10);

    lv_obj_t * label = lv_label_create(btn1, nullptr);
    lv_label_set_text(label, "Click me");
}


int main() {
  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  button_led_example();


  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(5 * 1000);
  }
}
