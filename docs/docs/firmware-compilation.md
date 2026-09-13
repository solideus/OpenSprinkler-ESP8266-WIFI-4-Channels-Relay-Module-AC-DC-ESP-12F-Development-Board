# Firmware Compilation

The firmware compilation instructions below are for OpenSprinkler **v3.x and v2.3** only.
<br>For RPi and Linux-based OpenSprinkler (OSPi), follow the [OSPi installation instructions](https://openthings.freshdesk.com/support/solutions/articles/5000631599-installing-and-updating-the-unified-firmware-on-ospi).

## Environment Setup

1. Clone this repository with required submodules, then enter the source directory:

        git clone --recurse-submodules https://github.com/OpenSprinkler/OpenSprinkler-Firmware.git
        cd OpenSprinkler-Firmware

2. Install the latest LTS version of Node.js from [https://nodejs.org/](https://nodejs.org/) if you don't already have it.
3. In the source directory, run `npm install html-minifier-terser`.
4. Install Visual Studio Code (VS Code) from [https://code.visualstudio.com/](https://code.visualstudio.com/), if you don't already have it.
5. Launch VS Code and install the **PlatformIO** extension.

---

## Building the Firmware

1. In VS Code, click `File -> Open Folder` and select the `OpenSprinkler-Firmware` folder.
2. PlatformIO will recognize the `platformio.ini` file in that folder, which contains all the libraries and settings needed to compile the firmware.
3. Select `os3x_esp8266` as the PlatformIO build environment for OpenSprinkler v3.x.
4. Click the **PlatformIO: Build** button (with the checkmark icon ✓) in the blue status bar at the bottom of the screen to build the firmware.

---
