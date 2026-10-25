#pragma once
#include <Arduino.h>

// Personal credentials belong in Secrets.h, which Git ignores.
// The example values allow verification builds without exposing real credentials.
#if __has_include("Secrets.h")
#include "Secrets.h"
#else
#include "Secrets.example.h"
#endif

inline constexpr char CITY_NAME[] = "Bengaluru";
inline constexpr char LATITUDE[] = "12.9719";
inline constexpr char LONGITUDE[] = "77.5937";
inline constexpr char TIMEZONE_POSIX[] = "IST-5:30";
inline constexpr uint32_t UPDATE_INTERVAL_MS = 15UL * 60UL * 1000UL;
inline constexpr uint32_t RETRY_INTERVAL_MS = 60UL * 1000UL;
inline constexpr uint32_t AUTO_PAGE_INTERVAL_MS = 6500;
inline constexpr uint8_t DISPLAY_ROTATION = 1;
inline constexpr uint8_t TOUCH_ROTATION = 1;
inline constexpr int TOUCH_CS_PIN = 33;
inline constexpr int TOUCH_IRQ_PIN = 36;
inline constexpr int TOUCH_CLK_PIN = 25;
inline constexpr int TOUCH_MISO_PIN = 39;
inline constexpr int TOUCH_MOSI_PIN = 32;
