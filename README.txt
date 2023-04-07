============================================
==== OpenSprinkler AVR/RPI/BBB Firmware ====
============================================

This is a unified OpenSprinkler firmware for Arduino, and Linux-based OpenSprinklers such as OpenSprinkler Pi.

For OS (Arduino-based OpenSprinkler) 2.x:
https://openthings.freshdesk.com/support/solutions/articles/5000165132-how-to-compile-opensprinkler-firmware

For OSPi/OSBO or other Linux-based OpenSprinkler:
https://openthings.freshdesk.com/support/solutions/articles/5000631599-installing-and-updating-the-unified-firmware

--------------------------------------------

This modification with respect to the original is capable of controlling the relays included in the board

Model: ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board

Probably the cheapest board on which you will be able to mount OpenSprinkler

The lines on the RTC module have been recovered. Now with update 2.1.9 (9) It is only updated if the module exists.

The sensors have been nested to the GPIO1 and GPIO3 ports. They have only been tested in button quality.

I have tested an SSD1306 oled screen connected to the pins of the board and it works correctly
  
  3,3v   -> vcc
  g      -> gnd
  gpio5  -> scl
  gpio4  -> sda
  gpio1  ___.-.___ g                 Sensor 1
  gpio3  ___.-.___ g                 Sensor 2
  gpio2  ___.-.___ g                 b1 (button 1) "INPUT_PULLUP"
  gpio15 ___.-.___ 3,3v              b2 (button 2) "INPUT_PULLDOWN"
  gpio0  ___.-.___ g                 b3 (button 3) "INPUT_PULLUP"

Changed SSD1306Display.h "Wire.setClock(100000L)" due to incompatibility with RTC DS1306

I haven't tested with sensors and other components. 

vampywiz17: 

I updated all affected files to 2.1.9(11) version. it is a minor changes. 2.1.9(11) the last version, that easy to update use with ESP boards. with 2.2.0 is to much changes, that i able to rewrite it. I hope somebody will do this in the future.

Suggestions are welcome

Credits: Thanks to the forum user Tobasco
https://opensprinkler.com/forums/topic/change-firmware-to-control-stations-directly-via-gpio-pins-relays/

============================================
Questions and comments:
http://www.opensprinkler.com
============================================
