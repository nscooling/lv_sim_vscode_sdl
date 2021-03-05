
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/

 #include "Clock.h"
 #include <iostream>

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

  auto start = std::chrono::system_clock::now();
  std::time_t t = std::time(0);   // get time now
  std::tm* now = std::localtime(&t);
  dateTimeController.SetTime(now->tm_year + 1900, (now->tm_mon + 1), now->tm_mday, 0, 0, 0, 0, 0);

  Applications::Screens::Clock display{
    &displayApp,
    dateTimeController,
    batteryController,
    bleController,
    notificatioManager,
    heartRateController
  };


  while (1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_task_handler();
    usleep(5 * 1000);
    dateTimeController.UpdateTime(0);
    display.Refresh();
  }

}

