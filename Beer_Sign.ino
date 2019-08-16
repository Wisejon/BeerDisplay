
// Graphics Libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                       // in which case, set this #define pin to -1!
#define TFT_DC     8

String leftBeerName = "WiseBrew Rye";
String leftBeerStyle = "Rye Ale";
String leftBeerTapDate = "08/01/2019";

String rightBeerName = "Laurelwood Sparkle Sparkle";
String rightBeerStyle = "Aussie Ale";
String rightBeerTapDate = "08/13/2019";

int displayHeight = 160;
int displayWidth = 128;

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup(void) {
  Serial.begin(9600);
  
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  Serial.println("done");
  delay(1000);
  
  Serial.println("Left Tap:");
  Serial.println(leftBeerName);
  Serial.println(leftBeerStyle);
  Serial.println(leftBeerTapDate);

  Serial.println("Right Tap:");
  Serial.println(rightBeerName);
  Serial.println(rightBeerStyle);
  Serial.println(rightBeerTapDate);

  beerStart();
  delay(5000);
}

void loop() {
  beerText("Left Tap",leftBeerName, leftBeerStyle, leftBeerTapDate);
  delay(5000);
  tft.fillScreen(ST77XX_BLACK);
  delay(500);
  beerText("Right Tap", rightBeerName, rightBeerStyle, rightBeerTapDate);
  delay(5000);
}

void background(){
  tft.fillScreen(ST77XX_BLACK);
  //draw white rectangle at top
  tft.fillRect(0,0,displayWidth,48, ST77XX_WHITE);
}

void beerText(String tap,String name,String style,String tapDate){
  
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  //draw rectangle at top
  tft.fillRect(0,0,128,48, ST77XX_WHITE);
  //fill with text
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(16,16);
  tft.println(tap);

  // set beer name
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(0);  
  if(name.length() > 20 ){
    //write out 2 lines of name
    //write line 1
    tft.setCursor(5,60);
    tft.println(name.substring(0,19));
    //write line 2
    tft.setCursor(5,70);
    tft.println(name.substring(19));
  } else{
    tft.setCursor(5,70);
    tft.println(name);
  }

  //Draw Beer Style
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5,90);
  tft.println("Style:");
  tft.setCursor(5,100);
  tft.println(style);
  //Draw Tap Date
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(5,120);
  tft.println("Tap Date:");
  tft.setCursor(5,130);
  tft.println(tapDate);
}

void beerStart() {
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(35, 40);
  tft.println("Beers");
  tft.setCursor(53, 72);
  tft.println("On");
  tft.setCursor(47, 104);
  tft.println("Tap");
}
