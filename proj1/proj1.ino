/*
  Display a scrolling image (from image.h) on a TFT
  Adapted from https://github.com/VolosR/ImageScroll
*/

#include "TFT_eSPI.h"
#include "landscape.h"
#include <Adafruit_GFX.h>

#define RAIN1 0x73AE
#define RAIN2 0x6B4D

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int screenW=240;
int screenH=135;

const int numDrops = 100;

int raindrops[numDrops][2];

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,screenW,screenH,landscape);

  for(int i = 0; i < numDrops; i++) {
    int randX = random(0, screenW);
    int randY = random(0-screenH+5, 0);
    raindrops[i][0] = randX;
    raindrops[i][1] = randY;
    tft.drawRect(randX, randY, 0, 5, RAIN1);
    tft.drawRect(randX+1, randY, 0, 5, RAIN2);

  }

}
void loop() {
  for(int i = 0; i < numDrops; i++) {
    raindrops[i][1] = raindrops[i][1]+1;
    drawRaindrop(i);
  }
  delay(10);
}

void drawRaindrop(int i) {
  if(raindrops[i][0] < screenW) {
    if(raindrops[i][1]-1 < screenH) {
      tft.drawPixel(raindrops[i][0], raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0], raindrops[i][1]-1));
    }
    if(raindrops[i][1]+6 < screenH) {
      tft.drawPixel(raindrops[i][0], raindrops[i][1]+6, RAIN1);
    }
   }

  if(raindrops[i][0]+1 < screenW) {
    if(raindrops[i][1]-1 < screenH) {
      tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0]+1, raindrops[i][1]-1));
    }
    if(raindrops[i][1]+6 < screenH) {
      tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]+6, RAIN2);
    }
  }
}

int getPixelFromLandscape(int x, int y) {
  return landscape[screenW * y + x];
}