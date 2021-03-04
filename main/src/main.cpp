
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/

 #include "Clock.h"

using namespace Pinetime;

#include <unistd.h>
#include "lvgl/lvgl.h"
// #include "lv_examples/lv_examples.h"
#include "hal_init.h"

#include "components/Doubles.h"

int main()
{

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

  // lv_demo_widgets();
//  lv_demo_printer();
  Controllers::DateTime dateTimeController{};
  Controllers::Battery batteryController{};
  Controllers::Ble bleController{};
  Controllers::NotificationManager notificatioManager{};
  Controllers::HeartRateController heartRateController{};

  Applications::DisplayApp displayApp{};


  Applications::Screens::Clock display{
    &displayApp,
    dateTimeController,
    batteryController,
    bleController,
    notificatioManager,
    heartRateController
  };

  display.Refresh();

  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(5 * 1000);
  }

}

