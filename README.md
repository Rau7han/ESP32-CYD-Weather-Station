# ESP32 CYD Weather Station

<p align="center">
  <img src="images/Teal%20Weather%20Station%20Product%20Shot.png" alt="ESP32 CYD weather station product view" width="720">
</p>

<p align="center">
  A polished 320×240 touchscreen weather dashboard for the ESP32 Cheap Yellow Display (CYD).
</p>

<p align="center">
  <img src="https://img.shields.io/badge/platform-ESP32-blue?style=flat-square" alt="ESP32">
  <img src="https://img.shields.io/badge/display-ILI9341-00a6a6?style=flat-square" alt="ILI9341">
  <img src="https://img.shields.io/badge/touch-XPT2046-00a6a6?style=flat-square" alt="XPT2046">
  <img src="https://img.shields.io/badge/Arduino%20core-3.2.0-00979D?style=flat-square" alt="Arduino ESP32 core 3.2.0">
  <img src="https://img.shields.io/badge/release-v3.1-informational?style=flat-square" alt="Release v3.1">
</p>

## Overview

This project turns an ESP32-WROOM-32 CYD into a standalone internet-connected
weather station. It combines live current conditions, a four-day forecast,
weather icons, moon phase, sunrise/sunset, wind direction, UV, and system
status in a touch-friendly landscape interface.

The firmware is configured for a **320×240 ILI9341 CYD with XPT2046 resistive
touch and 4 MB flash**. The default location is Bengaluru, India, using IST
(UTC+05:30), but the location and update settings can be changed in
`All_Settings.h`.

> **New to the project?** Start with [START_HERE.md](START_HERE.md) for the
> short upload checklist, then use the detailed setup below when configuring
> Arduino IDE.

## See it in action

### Touchscreen pages

| Home | Forecast |
| --- | --- |
| ![Home page](images/0-home.png) | ![Four-day forecast page](images/1-forecast.png) |

| Conditions | System |
| --- | --- |
| ![Conditions page](images/2-conditions.png) | ![System page](images/3-system.png) |

### Product views

<p align="center">
  <img src="images/Angled%20Weather%20Dashboard%20Display%20Module.png" alt="Angled view of the weather dashboard" width="48%">
  <img src="images/Teal%20Weather%20Station%20Dashboard.png" alt="Teal weather station dashboard" width="48%">
</p>

<p align="center">
  <img src="images/Turquoise%20Four-Day%20Weather%20Station.png" alt="Four-day forecast product view" width="48%">
  <img src="images/Teal%20Weather%20Display%20with%20System%20Information.png" alt="System information product view" width="48%">
</p>

All images are stored in the [`images/`](images/) directory so the README
continues to render when the repository is cloned or uploaded to GitHub.

## Features

- Live current conditions from OpenWeather.
- Four-day forecast grouped by local calendar day.
- Temperature, feels-like temperature, humidity, pressure, wind, rain, and UV.
- Sunrise, sunset, local clock, moon phase, and weather condition icons.
- Four touch pages: **Home**, **Forecast**, **Conditions**, and **System**.
- Tap navigation, left/right swipes, and automatic page cycling.
- Touchscreen calibration saved in ESP32 NVS.
- HTTPS certificate verification and time synchronization before API requests.
- LittleFS assets for fonts, weather icons, wind arrows, moon phases, and splash screen.
- Retains valid old weather data during temporary network or API failures.

## Hardware

| Part | Required configuration |
| --- | --- |
| Board | ESP32-WROOM-32 CYD / ESP32 Dev Module |
| Display | 2.8-inch 320×240 ILI9341 TFT |
| Touch | XPT2046 resistive touchscreen |
| Flash | 4 MB |
| Wi-Fi | 2.4 GHz |
| Power | USB |

The verified display wiring uses TFT_eSPI setup
[`Setup801_ESP32_CYD_ILI9341_240x320.h`](Setup801_ESP32_CYD_ILI9341_240x320.h).
An ST7789 reference setup is also included, but the release build is tested on
the ILI9341 hardware.

## Quick start

### Requirements

- Arduino IDE **2.2.1 or newer**
- ESP32 board package **3.2.0** by Espressif Systems
- A 2.4 GHz Wi-Fi network
- An activated OpenWeather API key
- A compatible ESP32 CYD board

### 1. Install the ESP32 board package

In Arduino IDE, open **Preferences** and add this Boards Manager URL:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

Then open **Boards Manager** and install **esp32 by Espressif Systems,
version 3.2.0**. See the [official ESP32 installation guide][esp32-install].

### 2. Install the bundled libraries

Use **Sketch → Include Library → Add .ZIP Library** for each archive in
[`libraries/`](libraries/):

| Library | Bundled version |
| --- | --- |
| TFT_eSPI, configured for the CYD ILI9341 | 2.5.44 |
| TJpg_Decoder | 1.1.0 |
| ArduinoJson | 7.4.2 |
| XPT2046_Touchscreen | 1.4 |

The bundled TFT_eSPI library already contains the tested CYD configuration. If
you use another TFT_eSPI installation, apply the supplied
`Setup801_ESP32_CYD_ILI9341_240x320.h` to its `User_Setup.h` and keep the
default `#include <User_Setup.h>` selected in `User_Setup_Select.h`.

### 3. Configure credentials

Copy:

```text
Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/Secrets.example.h
```

to `Secrets.h` in the same folder, then enter your Wi-Fi credentials and API
key. `Secrets.h` is ignored by Git and must never be committed. Location,
timezone, pins, and refresh intervals are configured in `All_Settings.h`.

### 4. Open the complete sketch

Open this file in Arduino IDE:

```text
Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/
└── Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02.ino
```

Keep all `.ino`, `.h`, `.cpp`, and `data/` files together. Arduino IDE will
compile the supporting source files automatically.

### 5. Select these board settings

| Arduino IDE option | Value |
| --- | --- |
| Board | ESP32 Dev Module |
| CPU Frequency | 240 MHz |
| Flash Size | 4 MB (32Mb) |
| Flash Mode | DIO |
| Flash Frequency | 40 MHz |
| Partition Scheme | No OTA (2MB APP/2MB SPIFFS) |
| PSRAM | Disabled |
| Upload Speed | 115200 |
| Erase All Flash Before Sketch Upload | Disabled |

The menu calls the data partition **SPIFFS**, but this firmware mounts it as
LittleFS. The selected partition must provide the expected filesystem layout.

### 6. Upload the sketch and LittleFS data

1. Click **Verify**, then **Upload**.
2. Install the bundled
   `tools/littlefs-uploader/arduino-littlefs-upload-1.6.3.vsix`. Installation
   instructions are in [`tools/littlefs-uploader/INSTALL.txt`](tools/littlefs-uploader/INSTALL.txt).
3. Close Serial Monitor and keep the same board, port, and partition settings.
4. Open the command palette with **Ctrl+Shift+P** (macOS: **Cmd+Shift+P**).
5. Run **Upload LittleFS to Pico/ESP8266/ESP32**.
6. Reset the board.

The uploader sends the sketch's `data/` directory, including the fonts, moon
phases, wind arrows, weather icons, and splash image. Serial Monitor runs at
**115200 baud** and reports startup, asset checks, network updates, retries,
and touch calibration.

## Touch controls

- Tap the footer labels to open **Home**, **Forecast**, **Conditions**, or **System**.
- Swipe left or right to change pages.
- Tap the left or right side of the page to move backward or forward.
- Hold any page for two seconds, or choose **System → Calibrate**, to recalibrate touch.
- Hold and release each of the four calibration targets. Calibration persists in NVS.
- **System → Auto** cycles pages every 6.5 seconds and survives reboot.
- **System → Refresh** requests an immediate weather update.

The System page shows API/network status and the countdown to the next update or
retry. Repeated refresh requests are ignored while an update is already running.

## Weather data

- **Current conditions:** OpenWeather `/data/2.5/weather`.
- **Forecast:** OpenWeather `/data/2.5/forecast`. The next four local calendar
  days aggregate available three-hour samples for minimum/maximum temperature
  and rain. Description, pressure, humidity, and wind use the sample nearest
  local noon.
- **UV:** Open-Meteo air-quality data using `hourly=uv_index&timeformat=unixtime`.
  UV can be zero at night.
- **Refresh:** every 15 minutes, with a 60-second retry after a failure.
- **Security:** HTTPS uses the included public trust anchors. NTP time
  synchronization must succeed before HTTPS requests begin.

## Optional build and tests

Install [Arduino CLI][arduino-cli] and the same ESP32 3.2.0 board core. From
the repository root:

```sh
arduino-cli core update-index --additional-urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core install esp32:esp32@3.2.0 --additional-urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
python3 tools/build.py
python3 tools/test.py
```

Python 3.9+, `g++`, and a C library providing `strlcpy` are needed for the
optional host checks. Generated files remain under `.build/`.

## Project structure

| Path | Purpose |
| --- | --- |
| `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/DisplayUI.*` | Pages, rendering, splash screen, and asset checks |
| `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/WeatherNetwork.*` | HTTPS updates, retries, and API-key fallback |
| `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/WeatherJson.*` | API response validation and parsing |
| `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/WeatherModel.*` | Forecast model, gestures, and calibration state |
| `Esp32_CYD_TFT_eSPI_OpenWeather_LittleFS_v02/data/` | Runtime fonts, icons, moon phases, wind arrows, and splash image |
| `libraries/` | Tested library archives and SHA-256 manifest |
| `tests/` | Host-side weather JSON and model tests |
| `images/` | README screenshots and project photos |

## Troubleshooting

### Blank screen after upload

Use the bundled configured TFT_eSPI library, or replace the installed
`User_Setup.h` with `Setup801_ESP32_CYD_ILI9341_240x320.h`. Also confirm:

- **No OTA (2MB APP/2MB SPIFFS)**
- **DIO**
- **40 MHz**
- **4 MB flash**

The firmware checks the TFT setup and partition selection at compile time.

### `FATAL: LittleFS mount failed`

Verify the partition scheme, then upload the complete `data/` directory again
with the same board, port, and partition selection used for the sketch upload.

### No weather data

Confirm that `Secrets.h` contains valid 2.4 GHz Wi-Fi credentials and an
activated API key. Wait for NTP synchronization before expecting the first
HTTPS request. The System page and Serial Monitor show the current status.

## Credits and license

This project adapts Michael Fehr's
[ESP32 CYD Weather Station with Forecast][michael-fehr], Bodmer's TFT/LittleFS
graphics work, and ThingPulse/Daniel Eichhorn's
[color weather station][thingpulse]. The landscape geometry follows the
supplied HTML reference.

See [`LICENSE`](LICENSE), [`THIRD_PARTY_NOTICES.txt`](THIRD_PARTY_NOTICES.txt),
and the bundled libraries' original licensing notices. API data and services
remain subject to their providers' terms.

[arduino-cli]: https://docs.arduino.cc/arduino-cli/installation/
[esp32-install]: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
[michael-fehr]: https://github.com/AndroidCrypto/ESP32_CYD_Weather_Station_With_Forecast
[thingpulse]: https://github.com/ThingPulse/esp8266-weather-station-color
