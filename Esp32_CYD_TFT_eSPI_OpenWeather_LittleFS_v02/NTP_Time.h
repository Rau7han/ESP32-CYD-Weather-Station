#pragma once
#include <Arduino.h>
#include <time.h>
#include "All_Settings.h"
inline bool clockValid() { return time(nullptr) > 1700000000; }
inline void initClock() {
  // POSIX sign is reversed: IST-5:30 means UTC+05:30, with no DST.
  configTzTime(TIMEZONE_POSIX, "time.google.com", "pool.ntp.org", "time.cloudflare.com");
}
inline String localTimeText(time_t utc, const char* format = "%H:%M") {
  if (utc <= 0) return "--:--";
  struct tm local; localtime_r(&utc, &local);
  char output[40]; strftime(output, sizeof(output), format, &local);
  return String(output);
}
