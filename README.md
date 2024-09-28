# Rainscape

This project is an introduction to coding on a LilyGo TTGO T-display ESP32 through the creation of a simple, calming landscape. The display takes an image of a cloudy lake and adds raindrops and a ripple effect (when the raindrops land on the water) to the image, converting the original image into a dynamic, digital viewscape.

## Project GIF
![](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExdGcwd2E4NnAwamp3cTc0ZnlsaHpqdjgzdmR1NjFjeThjaGtzY3c3cCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/FPG76PMqcvdcpz8vX8/giphy.gif)

## Recreation
To recreate this project, you will need a LilyGo TTGO T-display ESP32 device and a cable with one end for connecting to your computer (usb or usb-c) and the other end for connecting to the LilyGo (usb-c)

### Setup

1. Download the Arduino IDE [here](https://www.arduino.cc/en/software)
2. Install the TTGO T-Display driver [here](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)
3. In Arduino, open up the Arduino Library Manger and install `tft_espi` by Bodmer 
    1. Go to Tools > Library Manager
    2. Search for `tft_espi` and hit the install button
4. Navigate to the library, e.g. `Documents/Arduino/libraries/tft_espi`
5. Open up the file `Arduino/libraries/TFT_eSPI/User_Setup_Select.h`
6. Comment out the line `#include <User_setup.h>`
7. Uncomment the line `include <User_Setups/Setup25_TTGO_T_Display.h>`
8. Follow the instructions [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) to install the ESP 32 library under *Installing using Arduino IDE*

### Install
1. Clone the github repository
2. Open the cloned repository in the Arduino IDE
3. Upload sketch to your LilyGO TTGO T-display

NOTE: Make sure the `landscape.h` file is in the same folder as `rainscape.ino`

### Presentation
There are many ways to present this project if you want it to be independent from the computer. To create a hanging display, you will need a LiPo battery, string, a popsicle stick, and an envelope with two small holes (for the thread) and one big hole (which should be the same size as the display on the TTGO). You can follow the steps linked [here](https://coms3930.notion.site/Module-1-Install-10a350cc6f058045b899e7d3c2a3c8f5) to set up the presentation.
