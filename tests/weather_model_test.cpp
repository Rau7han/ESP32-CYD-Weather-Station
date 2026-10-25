#include "WeatherModel.h"
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
int main() {
  // A UTC date boundary occurs 5.5 hours after Bengaluru's boundary.
  const time_t day = 20750;
  const time_t midnightIst = day * 86400 - IST_OFFSET_SECONDS;
  assert(bengaluruDay(midnightIst - 1) == day - 1);
  assert(bengaluruDay(midnightIst) == day);
  WeatherPoint points[7];
  points[0].timestamp = midnightIst + 10 * 3600; // Today must not enter tomorrow's row.
  points[0].low = -99; points[0].high = 99;
  const int hours[] = {1, 7, 10, 13, 19, 22};
  for (int i = 1; i < 7; ++i) {
    points[i].timestamp = midnightIst + 86400 + hours[i - 1] * 3600;
    points[i].low = 15 + i; points[i].high = 20 + i; points[i].rain = 0.5;
    points[i].precipitationProbability = i / 10.0f;
  }
  DayForecast days[4]; buildDailyForecast(points, 7, midnightIst + 20 * 3600, days);
  assert(days[0].valid && days[0].samples == 6);
  assert(days[0].low == 16 && days[0].high == 26 && days[0].rain == 3.0f);
  assert(std::fabs(days[0].probability - 0.6) < 0.001);
  assert(days[0].representative.timestamp == midnightIst + 86400 + 13 * 3600);
  assert(!days[1].valid && !days[2].valid && !days[3].valid);
  // No hard-coded offset of N array entries: missing slots cannot shift the day.
  points[0].timestamp = midnightIst + 3 * 86400 + 12 * 3600;
  buildDailyForecast(points, 1, midnightIst, days);
  assert(!days[0].valid && !days[1].valid && days[2].valid && !days[3].valid);
  assert(std::strcmp(weatherIconName(800, "01n"), "clear-night") == 0);
  assert(std::strcmp(weatherIconName(801, "02d"), "partly-cloudy-day") == 0);
  assert(std::strcmp(weatherIconName(500, "10d"), "lightRain") == 0);
  assert(std::strcmp(weatherIconName(511, "13d"), "sleet") == 0);
  assert(std::strcmp(weatherIconName(200, "11d"), "thunderstorm") == 0);
  assert(std::strcmp(weatherIconName(0, ""), "unknown") == 0);
  assert(std::strcmp(windDirection(-45), "NW") == 0);
  assert(std::strcmp(windDirection(360), "N") == 0);
  assert(pageForGesture(0, 250, 120, 30, 120) == 1);
  assert(pageForGesture(0, 30, 120, 250, 120) == 3);
  assert(pageForGesture(0, 285, 231, 285, 231) == 3);
  assert(pageForGesture(2, 20, 100, 20, 100) == 1);
  assert(pageForGesture(2, 150, 10, 151, 100) == 2); // Vertical movement is not a tap.
  assert(wrapPage(-1) == 3 && wrapPage(4) == 0);
  assert(secondsUntil(1000, 2500) == 2);
  assert(secondsUntil(2500, 2500) == 0);
  assert(secondsUntil(3000, 2500) == 0);
  assert(secondsUntil(UINT32_MAX - 499, 500) == 1);
  const int regular[4][2] = {{300,400},{3700,400},{3700,3600},{300,3600}};
  const int rotated[4][2] = {{3600,300},{3600,3700},{400,3700},{400,300}};
  const int bad[4][2] = {{100,100},{100,100},{100,100},{100,100}};
  TouchCalibration c;
  for (auto raw : {regular, rotated}) {
    assert(fitTouchCalibration(raw, c));
    int x, y; mapTouch(c, (raw[0][0]+raw[2][0])/2, (raw[0][1]+raw[2][1])/2, x, y);
    assert(std::abs(x-160) <= 1 && std::abs(y-110) <= 1);
  }
  assert(!fitTouchCalibration(bad, c));
  int outsideX, outsideY;
  mapTouch(TouchCalibration{}, -999, 9999, outsideX, outsideY);
  assert(outsideX == 0 && outsideY == 239);
  std::cout << "PASS: IST date rollover, daily aggregation, icons, navigation, affine calibration\n";
}
