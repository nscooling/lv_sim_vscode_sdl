#include "DateTimeController.h"

#include <chrono>

namespace Pinetime {
  namespace Controllers {
        void DateTime::SetTime(std::uint16_t year, 
        std::uint8_t month, 
        std::uint8_t day, 
        std::uint8_t dayOfWeek, 
        std::uint8_t hour, 
        std::uint8_t minute, 
        std::uint8_t second, 
        std::uint32_t systickCounter)
        {
            this->year = year;
            this->month = static_cast<Months>(month);
            this->day = day;
            if(dayOfWeek != 0){
                this->dayOfWeek = static_cast<Days>(dayOfWeek);
            } else {
                this->dayOfWeek = Days::Sunday;
            }
            this->hour = hour;
            this->minute = minute;
            this->second = second;
        }

        void DateTime::UpdateTime(std::uint32_t systickCounter){
            currentDateTime =  std::chrono::system_clock::now();
            auto t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto now = std::localtime(&t_c);
            SetTime((now->tm_year + 1900),
                (now->tm_mon + 1),
                now->tm_mday,
                now->tm_wday,
                (now->tm_hour + 1),
                now->tm_min,
                now->tm_sec,
                0
            );

        }
  }
}