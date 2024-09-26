#include "TFT_eSPI.h"
#include "landscape.h"
#include <Adafruit_GFX.h>

#define RAIN1 0x73AE
#define RAIN2 0x6B4D
#define rippleLight 0xa554
#define rippleDark 0x8c51

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int screenW=240;
int screenH=135;

const int numDrops = 100;
const int minRaindropHeight = 6;
const int maxRaindropHeight = 10;
const int raindropWidthDivider = 8;
const int rippleDuration = 30;

int raindrops[numDrops][3];
int ripples[numDrops][3];

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

    if(ripples[i][2] > 0) {
      ripples[i][2] -= 1;
      if(ripples[i][2] == 0) {
        undoRipple(i);
      }
    }
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
      if(raindrops[i][2] != maxRaindropHeight && shouldDrawRipple(i)) {
        drawRipple(i);
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

bool shouldDrawRipple(int i) {
  if(raindrops[i][0] < 100 && raindrops[i][1]+raindrops[i][2] < 105) {
    return false;
  }
  return true;
}

bool lightWaterColor(int i) {
  if(raindrops[i][0] > 100 && raindrops[i][1]+raindrops[i][2] < 105) {
    return true;
  }
  return false;
}

void drawRipple(int i) {
  ripples[i][0] = raindrops[i][0];
  ripples[i][1] = raindrops[i][1] + raindrops[i][2];
  ripples[i][2] = rippleDuration;
  int x = ripples[i][0];
  int y = ripples[i][1];
  if(!lightWaterColor(i)) {
    tft.drawPixel(x, y+1, rippleDark);
    tft.drawPixel(x+1, y, rippleDark);
    tft.drawPixel(x+2, y, rippleDark);
    tft.drawPixel(x+3, y, rippleDark);
    tft.drawPixel(x+4, y, rippleDark);
    tft.drawPixel(x+5, y+1, rippleDark);
    tft.drawPixel(x+1, y+2, rippleDark);
    tft.drawPixel(x+2, y+2, rippleDark);
    tft.drawPixel(x+3, y+2, rippleDark);
    tft.drawPixel(x+4, y+2, rippleDark);
  }
  else {
    tft.drawPixel(x, y+1, rippleLight);
    tft.drawPixel(x+1, y, rippleLight);
    tft.drawPixel(x+2, y, rippleLight);
    tft.drawPixel(x+3, y, rippleLight);
    tft.drawPixel(x+4, y, rippleLight);
    tft.drawPixel(x+5, y+1, rippleLight);
    tft.drawPixel(x+1, y+2, rippleLight);
    tft.drawPixel(x+2, y+2, rippleLight);
    tft.drawPixel(x+3, y+2, rippleLight);
    tft.drawPixel(x+4, y+2, rippleLight);
  }
}

void undoRipple(int i) {
  int x = ripples[i][0];
  int y = ripples[i][1];

  tft.drawPixel(x, y+1, getPixelFromLandscape(x, y+1));
  tft.drawPixel(x+1, y, getPixelFromLandscape(x+1, y));
  tft.drawPixel(x+2, y, getPixelFromLandscape(x+2, y));
  tft.drawPixel(x+3, y, getPixelFromLandscape(x+3, y));
  tft.drawPixel(x+4, y, getPixelFromLandscape(x+4, y));
  tft.drawPixel(x+5, y+1, getPixelFromLandscape(x+5, y+1));
  tft.drawPixel(x+1, y+2, getPixelFromLandscape(x+1, y+2));
  tft.drawPixel(x+2, y+2, getPixelFromLandscape(x+2, y+2));
  tft.drawPixel(x+3, y+2, getPixelFromLandscape(x+3, y+2));
  tft.drawPixel(x+4, y+2, getPixelFromLandscape(x+4, y+2));
}