/*
  Display a scrolling image (from image.h) on a TFT
  Adapted from https://github.com/VolosR/ImageScroll
*/

#include "TFT_eSPI.h"
#include "landscape.h"

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int screenW=240;
int screenH=135;

void setup() {
tft.init();
tft.setRotation(1);
tft.setSwapBytes(true);
tft.fillScreen(TFT_BLACK);
tft.pushImage(0,0,screenW,screenH,landscape);

}
void loop() {

}