#pragma once 

namespace Pinetime {
  namespace Controllers {
    class Battery{
      public:
      int PercentRemaining() { return 100; }
      bool IsCharging() const { return true; }
      bool IsPowerPresent() const { return true; }
    };
    class Ble{
      public:
      bool IsConnected() { return false; }
    };
    class NotificationManager{
      public:
      bool AreNewNotificationsAvailable() { return true; };
    };
    class HeartRateController{
      public:
      enum class States { Stopped, NotEnoughData, NoTouch, Running};

      States State() const { return States::Running; }
      std::uint8_t HeartRate() const { return 75; }
    };
  }
  namespace Applications {
    class DisplayApp {};
  }
}
