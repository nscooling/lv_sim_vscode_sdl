#include "DateTimeController.h"

#include <chrono>

namespace Pinetime {
  namespace Controllers {
        void DateTime::SetTime(std::uint16_t year, std::uint8_t month, std::uint8_t day, std::uint8_t dayOfWeek, std::uint8_t hour, std::uint8_t minute, std::uint8_t second, std::uint32_t systickCounter){

        // std::uint32_t previousSystickCounter{};
        currentDateTime =  std::chrono::system_clock::now();
        // std::chrono::seconds uptime{};
        
        this->year = year;
        this->month = static_cast<Months>(month);
        this->day = day;
        this->dayOfWeek = static_cast<Days>(dayOfWeek);
        this->hour = hour;
        this->minute = minute;
        this->second = second;

        }

        void DateTime::UpdateTime(std::uint32_t systickCounter){
                currentDateTime =  std::chrono::system_clock::now();
        }
  }
}