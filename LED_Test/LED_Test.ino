#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include "FastLED.h"
#include "font.h"


///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 299

// Data pin that led data will be written out over
#define DATA_PIN 3

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
       Serial.begin(9600);
      // Uncomment one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
//      FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void lightUP(int start) {
  int end = 150 - start;
   for(int whiteLed = start; whiteLed < end; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
  
}


void drawPixel(int x, int y, CRGB color, bool doubleScale = false) {
  if (doubleScale) {
    drawPixel(2*x, 2*y, color);
    drawPixel(2*x+1, 2*y, color);
    drawPixel(2*x, 2*y+1, color);
    drawPixel(2*x+1, 2*y+1, color);
    return;
  }
  if ( x < 0 || x > 22 || y < 0 || y > 12) {
    return;
  }  
  int row = (12-y) * 23;
	int row_x;
	if (!(row%2)) {
		row_x = row + (22-x);
	}
	else {
		row_x = row + x;
	}
	leds[row_x] = color;
}

void drawLineY(int x,int y, int len, CRGB color, bool doubleScale = false) {
  for (int i = 0; i < len; i ++) {
    drawPixel(x, y+i, color, doubleScale);
  }  
}

void drawLineX(int x,int y, int len, CRGB color, bool doubleScale = false) {
  for (int i = 0; i < len; i ++) {
    drawPixel(x+i, y, color, doubleScale);
  }  
}

void drawCharacter(int x_start, int y_start, char letter, CRGB color, bool doubleScale = false) {
  //drawPixel(x_start, y_start, CRGB::Yellow);
  int index = char_to_index(letter);
  for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 3; j++) {
		//x_start +=j;
//                if (pgm_read_byte_near(font + index*15 + i*3 + j)) {
                if (pgm_read_byte_near(&font[index][i][j])) {
                  drawPixel(x_start + j, y_start + i, color, doubleScale);
                }
                else {
                    drawPixel(x_start + j, y_start + i, CRGB(0,0,0), doubleScale);

                }
                
	}
  }
  
}

void drawString(int x, int y, const char * message, CRGB color, bool doubleScale = false) {
  while (*message) {
     drawCharacter(x,y,*message, color, doubleScale);
     drawLineY(x + 3,y,5, CRGB::Black, doubleScale);
     x += 4;
     message++; 
  }
}




#define PI 3.14159265
#include <math.h>

void rainbowSeries(int ledNumbers) {
   for(int i = 0; i < ledNumbers; i++) {
     float input = (255/ledNumbers)*i; 
     hsv2rgb_rainbow(CHSV(input,200,200), leds[(i+10)%150]);
      FastLED.show();
      delay(10);
      leds[i] = CRGB( 0, 0, 0);

      Serial.print("LED #: ");
      Serial.print(i);
      Serial.print("\n");
   }
}
bool alternate = false;
CRGB color (0,0,0);

void loop() {
   //rainbowSeries(150);
   FastLED.show();
   CRGB color (CRGB::Yellow);
   if (alternate) {
     color = CRGB(0,0,255);
   }
 
   drawString(0,0,"830", color, true);
   //drawString(0, 7, "BOTT", color);
   Serial.print("something");

   delay(250);
   alternate = !alternate;

}
