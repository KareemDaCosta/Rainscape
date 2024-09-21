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
const int minRaindropHeight = 6;
const int maxRaindropHeight = 10;
const int raindropWidthDivider = 8;

int raindrops[numDrops][3];

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,screenW,screenH,landscape);

  for(int i = 0; i < numDrops; i++) {
    resetRaindrop(i);
  }

}
void loop() {
  for(int i = 0; i < numDrops; i++) {
    raindrops[i][1] = raindrops[i][1]+1;
    drawRaindrop(i);
  }
}

void drawRaindrop(int i) {
  const int raindropHeight = raindrops[i][2];

  if(hitWater(i)) {
    for(int y = raindrops[i][1]-1; y < raindrops[i][1] + raindropHeight; y++) {
      tft.drawPixel(raindrops[i][0], y, getPixelFromLandscape(raindrops[i][0], y));
      if(raindrops[i][2] > raindropWidthDivider) {
        tft.drawPixel(raindrops[i][0]+1, y, getPixelFromLandscape(raindrops[i][0]+1, y));
      }
    }
    resetRaindrop(i);
  }
  

  tft.drawPixel(raindrops[i][0], raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0], raindrops[i][1]-1));
  tft.drawPixel(raindrops[i][0], raindrops[i][1]+raindropHeight, RAIN1);

  if(raindrops[i][0]+1 < screenW) {
    tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0]+1, raindrops[i][1]-1));
    if(raindrops[i][2] > raindropWidthDivider) {
      tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]+raindropHeight, RAIN2);
    }
  }
}

int getPixelFromLandscape(int x, int y) {
  return landscape[screenW * y + x];
}

void resetRaindrop(int i) {
    int randHeight = random(minRaindropHeight, maxRaindropHeight);
    int randX = random(0, screenW);
    int randY = random(0-(screenH+randHeight), 0);
    raindrops[i][0] = randX;
    raindrops[i][1] = randY;
    raindrops[i][2] = randHeight;
}

bool hitWater(int i) {
  const int raindropHeight = raindrops[i][2];
  if(raindrops[i][1]+raindropHeight > screenH) {
    return true;
  }
  if(raindropHeight == maxRaindropHeight) {
    return false;
  }
  int randNumber = random(screenH/2, screenH * 3);
  return randNumber <= raindrops[i][1];
}