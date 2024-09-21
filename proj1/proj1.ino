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
const int raindropHeight = 6;

int raindrops[numDrops][2];

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
  delay(10);
}

void drawRaindrop(int i) {

  if(raindrops[i][1]+raindropHeight > screenH) {
    for(int y = raindrops[i][1]-1; y < screenH; y++) {
      tft.drawPixel(raindrops[i][0], y, getPixelFromLandscape(raindrops[i][0], y));
      tft.drawPixel(raindrops[i][0]+1, y, getPixelFromLandscape(raindrops[i][0], y));
    }
    resetRaindrop(i);
  }

  tft.drawPixel(raindrops[i][0], raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0], raindrops[i][1]-1));
  tft.drawPixel(raindrops[i][0], raindrops[i][1]+raindropHeight, RAIN1);

  if(raindrops[i][0]+1 < screenW) {
    tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]-1, getPixelFromLandscape(raindrops[i][0]+1, raindrops[i][1]-1));
    tft.drawPixel(raindrops[i][0]+1, raindrops[i][1]+raindropHeight, RAIN2);
  }
}

int getPixelFromLandscape(int x, int y) {
  return landscape[screenW * y + x];
}

void resetRaindrop(int i) {
    int randX = random(0, screenW);
    int randY = random(0-screenH+5, 0);
    raindrops[i][0] = randX;
    raindrops[i][1] = randY;
    tft.drawRect(randX, randY, 0, 5, RAIN1);
    tft.drawRect(randX+1, randY, 0, 5, RAIN2);
}