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

![ESP12F_Relay_X4](OpenSprinkler-ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board/blob/master/images/ESP12F_Relay_X4.jpg) 

Probably the cheapest board on which you will be able to mount OpenSprinkler

The lines on the RTC module have been recovered. Now with update 2.1.9 (9) It is only updated if the module exists.

The sensors have been nested to the GPIO1 and GPIO3 ports. They have only been tested in button quality.

I have tested an SSD1306 oled screen connected to the pins of the board and it works correctly
  
  3.3v   -> vcc
  g      -> gnd
  gpio5  -> scl
  gpio4  -> sda
  gpio1  ___.-.___ g                 Sensor 1
  gpio3  ___.-.___ g                 Sensor 2
  gpio2  ___.-.___ g                 b1 (button 1) "INPUT_PULLUP"
  gpio15 ___.-.___ 3.3v              b2 (button 2) "INPUT_PULLDOWN"
  gpio0  ___.-.___ g                 b3 (button 3) "INPUT_PULLUP"

Changed SSD1306Display.h "Wire.setClock(100000L)" due to incompatibility with RTC DS1306

I haven't tested with sensors and other components. 

StudioShemp:
I've extended on the excellent work of ThFischer, solideus and vampwiz17 to create a working (tested) 2.2.0(1) release. This includes an option to change the date format of the OLED to DD-MM in defines.h for those of us who find the US date format a little irksome. I've also created a 'define' in defines.h to flag the use of the ESP12F_RELAY_X4 board, and altered the code in main.cpp, OpenSprinkler.cpp and defines.h to run standard 2.2.0(1) or the version for this board depending on the value of that flag in defines.h. All sections of code using the flag as a condition are commented with /**ESP12F_RELAY_X4... */ to make maintaining easier for new releases

For this version (2.2.x) you will need to:
 - manually install the OpenThings-Framework-Firmware-Library into your Arduino IDE's library folder 
   (https://github.com/OpenThingsIO/OpenThings-Framework-Firmware-Library)

 - install the WebSockets Library by Markus Sattler using the Library Manager

See release notes for 2.2.0(1) at https://github.com/OpenSprinkler/OpenSprinkler-Firmware/releases/tag/220(1) 

![ESP12F_Relay_X4](OpenSprinkler-ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board/blob/master/images/OpenSprinkler220.jpg) 

Suggestions are welcome

Credits: Thanks to the forum user Tobasco
https://opensprinkler.com/forums/topic/change-firmware-to-control-stations-directly-via-gpio-pins-relays/

Also see additional tips from Tobasco at https://github.com/ThFischer/OpenSprinkler-for-ESP12F_Relay_X4 who provided foundational work on the use of this board. His repo includes tips on adding an external antenna, alterations to the DS1307 RTC for use with 3.3v and adding a relay protecting 'snubber' circuit if switching mains AC. 


============================================
Questions and comments:
http://www.opensprinkler.com
============================================

