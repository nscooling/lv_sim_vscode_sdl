#pragma once 

#include <cstdint>
#include <chrono>

namespace Pinetime {
  namespace Controllers {
    class DateTime {
      public:
        DateTime() = default;
        using time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
        enum class Days : std::uint8_t {Unknown, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
        enum class Months : std::uint8_t {Unknown, January, February, March, April, May, June, July, August, September, October, November, December};

        void SetTime(std::uint16_t year, std::uint8_t month, std::uint8_t day, std::uint8_t dayOfWeek, std::uint8_t hour, std::uint8_t minute, std::uint8_t second, std::uint32_t systickCounter);
        void UpdateTime(std::uint32_t systickCounter);
        std::uint16_t Year() const { return year; }
        Months Month() const { return month; }
        std::uint8_t Day() const { return day; }
        Days DayOfWeek() const { return dayOfWeek; }
        std::uint8_t Hours() const { return hour; }
        std::uint8_t Minutes() const { return minute; }
        std::uint8_t Seconds() const { return second; }

        time_point CurrentDateTime() const { return currentDateTime; }
        std::chrono::seconds Uptime() const { return uptime; }
      private:
        std::uint32_t previousSystickCounter{};
        time_point currentDateTime;
        std::chrono::seconds uptime{};
        
        std::uint16_t year{};
        Months month{};
        std::uint8_t day{};
        Days dayOfWeek{};
        std::uint8_t hour{};
        std::uint8_t minute{};
        std::uint8_t second{};
    };
  }
}