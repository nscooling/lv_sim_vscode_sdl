
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <unistd.h>

#include "hal_init.h"
#include "lv_examples/lv_examples.h"
#include "lvgl/lvgl.h"
#include "test_widgets.h"

int main() {
  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  // lv_demo_widgets();
  //  lv_demo_printer();
  exec();

  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(5 * 1000);
  }
}
