#include "WeatherModel.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
int32_t bengaluruDay(time_t utc) { return static_cast<int32_t>((utc + IST_OFFSET_SECONDS) / 86400); }
void buildDailyForecast(const WeatherPoint* points, size_t count, time_t nowUtc, DayForecast (&days)[4]) {
  const int32_t today = bengaluruDay(nowUtc);
  for (int i = 0; i < 4; ++i) { days[i] = DayForecast{}; days[i].localDay = today + 1 + i; }
  for (size_t i = 0; i < count; ++i) {
    const WeatherPoint& p = points[i];
    const int index = bengaluruDay(p.timestamp) - today - 1;
    if (index < 0 || index > 3) continue;
    DayForecast& day = days[index];
    const int distance = abs(static_cast<int>((p.timestamp + IST_OFFSET_SECONDS) % 86400) - 43200);
    const int oldDistance = abs(static_cast<int>((day.representative.timestamp + IST_OFFSET_SECONDS) % 86400) - 43200);
    if (!day.valid || distance < oldDistance) day.representative = p;
    if (!day.valid || p.low < day.low) day.low = p.low;
    if (!day.valid || p.high > day.high) day.high = p.high;
    day.rain += p.rain;
    if (p.precipitationProbability > day.probability) day.probability = p.precipitationProbability;
    ++day.samples;
    day.valid = true;
  }
}
const char* weatherIconName(uint16_t id, const char* icon) {
  const bool night = icon && strlen(icon) >= 3 && icon[2] == 'n';
  if (id >= 200 && id < 300) return "thunderstorm";
  if (id >= 300 && id < 400) return "drizzle";
  if (id == 500) return "lightRain";
  if (id == 511 || (id >= 611 && id <= 616)) return "sleet";
  if (id >= 500 && id < 600) return "rain";
  if (id >= 600 && id < 700) return "snow";
  if (id >= 700 && id < 800) return "fog";
  if (id == 800) return night ? "clear-night" : "clear-day";
  if (id == 801) return night ? "partly-cloudy-night" : "partly-cloudy-day";
  if (id >= 802 && id <= 804) return "cloudy";
  return "unknown";
}
const char* windDirection(int degrees) {
  static const char* directions[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
  const int normalized = ((degrees % 360) + 360) % 360;
  return directions[((normalized + 22) / 45) % 8];
}
int wrapPage(int page) { return (page % PAGE_COUNT + PAGE_COUNT) % PAGE_COUNT; }
uint32_t secondsUntil(uint32_t nowMs, uint32_t deadlineMs) {
  const int32_t remaining = static_cast<int32_t>(deadlineMs - nowMs);
  return remaining > 0 ? (static_cast<uint32_t>(remaining) + 999) / 1000 : 0;
}
int pageForGesture(int current, int x0, int y0, int x1, int y1) {
  const int dx = x1 - x0, dy = y1 - y0;
  if (abs(dx) >= 40 && abs(dx) > abs(dy)) return wrapPage(current + (dx < 0 ? 1 : -1));
  if (abs(dx) > 20 || abs(dy) > 20) return current;
  if (y0 >= 222 && y1 >= 222) return x1 / 80 < PAGE_COUNT ? x1 / 80 : current;
  return wrapPage(current + (x1 < 80 ? -1 : 1));
}
bool fitTouchCalibration(const int raw[4][2], TouchCalibration& r) {
  const float ax = raw[1][0] - raw[0][0], ay = raw[1][1] - raw[0][1];
  const float bx = raw[3][0] - raw[0][0], by = raw[3][1] - raw[0][1];
  const float determinant = ax * by - ay * bx;
  if (fabsf(determinant) < 100000) return false;
  r.xx = 280 * by / determinant; r.xy = -280 * bx / determinant;
  r.xc = 20 - r.xx * raw[0][0] - r.xy * raw[0][1];
  r.yx = -180 * ay / determinant; r.yy = 180 * ax / determinant;
  r.yc = 20 - r.yx * raw[0][0] - r.yy * raw[0][1];
  const float x = r.xx * raw[2][0] + r.xy * raw[2][1] + r.xc;
  const float y = r.yx * raw[2][0] + r.yy * raw[2][1] + r.yc;
  return fabsf(x - 300) < 20 && fabsf(y - 200) < 20;
}
void mapTouch(const TouchCalibration& c, int rx, int ry, int& x, int& y) {
  x = lroundf(c.xx * rx + c.xy * ry + c.xc); y = lroundf(c.yx * rx + c.yy * ry + c.yc);
  if (x < 0) x = 0;
  if (x >= DISPLAY_WIDTH) x = DISPLAY_WIDTH - 1;
  if (y < 0) y = 0;
  if (y >= DISPLAY_HEIGHT) y = DISPLAY_HEIGHT - 1;
}
