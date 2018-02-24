#define FASTLED_INTERNAL

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
#include "image-gen.h"
#include <math.h>


///
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
      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
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
		row_x = row + x;
	}
	else {
		row_x = row + (22-x);
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

void scrollMessage(int y, const char *message, CRGB color, bool doubleScale = false) {  
  for (int x = 22 - 11*doubleScale; x > (-4 * (int)strlen(message)); x--) {
    drawString(x, y, message, color, doubleScale);
    FastLED.show();
    delay(100);
    if (Serial.available() > 0){
      return;
    }
  }
}

void clearSign(){
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = 0;
  }
}


//#define PI 3.14159265
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

CRGB rainbowColor() {
    const float pi = 3.141592;
    static int x = 0;
    double red = -(0.5 *(sin((pi/5)*x))) + 1;
    double green = (0.5*(sin((pi/5)*x)) + (pi/3)) + 1;
    double blue = (0.5 *(sin((pi/5)*x)) + ((5*pi)/3)) + 1;
    x++;
    CRGB color (red*255, green*255, blue*255);
    return color;
  }

bool alternate = false;
bool textSize = true;
CRGB color = 0xff8800;

char message[100] = "GO RATPACK!";
/*const char* const black_list [] = {"SHIT", "FUCK", "CUNT", "CUCK", "NIGGER", "NIGGA", "ASS", "DICK", 
  "NUDES", "NUDE", "NOODS", "NOOD", "NOODES", "COCK", "BITCH", "FAGGOT", "GIL", "SEX", 
  "BOOB", "PENIS", "VAGINA", "PUSSY", "PU$$Y", "N00D", "N00DS", "WHORE", "SLUT", "DYKE", "NIBBA"
  "SHREK", "SHREKT", "SHREKED", "BASTARD", "PISS", "SUCK", "SUCC", "SUC", "DAMN", "TWAT"
  "ARSE", "ASSHOLE", "JERRY", "JESUS", "HELL", "BBC", "MILF", "GODDAMN", "BALLS", "BUTT", 
  "SHITTY", "KKK", "NUTS", "FUCKING", "GAY", "TRIGGERED", "STRIP", "STRIPPER", "PROSTITUTE",
  "PORN",   NULL}; */


const char s0[] PROGMEM = "SHIT";
const char s1[] PROGMEM =  "FUCK";
const char s2[] PROGMEM =  "CUNT";
const char s3[] PROGMEM =  "CUCK";
const char s4[] PROGMEM =  "NIGGER";
const char s5[] PROGMEM =  "NIGGA";
const char s6[] PROGMEM =  "ASS";
const char s7[] PROGMEM =  "DICK";
const char s8[] PROGMEM =    "NUDES";
const char s9[] PROGMEM =  "NUDE";
const char s10[] PROGMEM =  "NOODS";
const char s11[] PROGMEM =  "NOOD";
const char s12[] PROGMEM =  "NOODES";
const char s13[] PROGMEM =  "COCK";
const char s14[] PROGMEM =  "BITCH";
const char s15[] PROGMEM =  "FAGGOT";
const char s16[] PROGMEM =  "GIL";
const char s17[] PROGMEM =  "SEX";
const char s18[] PROGMEM =    "BOOB";
const char s19[] PROGMEM =  "PENIS";
const char s20[] PROGMEM =  "VAGINA";
const char s21[] PROGMEM =  "PUSSY";
const char s22[] PROGMEM =  "PU$$Y";
const char s23[] PROGMEM =  "N00D";
const char s24[] PROGMEM =  "N00DS";
const char s25[] PROGMEM =  "WHORE";
const char s26[] PROGMEM =  "SLUT";
const char s27[] PROGMEM =  "DYKE";
const char s28[] PROGMEM =  "NIBBA"  "SHREK";
const char s29[] PROGMEM =  "SHREKT";
const char s30[] PROGMEM =  "SHREKED";
const char s31[] PROGMEM =  "BASTARD";
const char s32[] PROGMEM =  "PISS";
const char s33[] PROGMEM =  "SUCK";
const char s34[] PROGMEM =  "SUCC";
const char s35[] PROGMEM =  "SUC";
const char s36[] PROGMEM =  "DAMN";
const char s37[] PROGMEM =  "TWAT"  "ARSE";
const char s38[] PROGMEM =  "ASSHOLE";
const char s39[] PROGMEM =  "JERRY";
const char s40[] PROGMEM =  "JESUS";
const char s41[] PROGMEM =  "HELL";
const char s42[] PROGMEM =  "BBC";
const char s43[] PROGMEM =  "MILF";
const char s44[] PROGMEM =  "GODDAMN";
const char s45[] PROGMEM =  "BALLS";
const char s46[] PROGMEM =  "BUTT";
const char s47[] PROGMEM =    "SHITTY";
const char s48[] PROGMEM =  "KKK";
const char s49[] PROGMEM =  "NUTS";
const char s50[] PROGMEM =  "FUCKING";
const char s51[] PROGMEM =  "GAY";
const char s52[] PROGMEM =  "TRIGGERED";
const char s53[] PROGMEM =  "STRIP";
const char s54[] PROGMEM =  "STRIPPER";
const char s55[] PROGMEM =  "PROSTITUTE";
const char s56[] PROGMEM =   "PORN";
const char* const black_list[] PROGMEM = {s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31,s32,s33,s34,s35,s36,s37,s38,s39,s40,s41,s42,s43,s44,s45,s46,s47,s48,s49,s50,s51,s52,s53,s54,s55,s56,'\0'};
char buffer[99];

void loop() {
     clearSign();
 //  for (int x = 0; x < 23; x ++) {
 //   for (int y = 0; y < 13; y++) {
 //      color = (pgm_read_byte_near(&pxl[x][y]));
 //       Serial.print(pgm_read_byte_near(&pxl[x][y][0]));
 //       Serial.print('\n');
 //      //CRGB color(x*10,y*13,0);
 //      drawPixel(x, y, color);
 //    }
 // }
 //   //rainbowSeries(150);
 //   FastLED.show();
 //   return;
 //   CRGB color (CRGB::Yellow);
 //   if (alternate) {
 //     color = CRGB(0,0,255);
 //   }
   
   
   // scrollMessage(0,"THE QUICK BROWN FOX JUMPED OVER THE LAZY DOGS",color, true);
   // //drawString(0, 0, "COLIN IS COOL", color);
   // Serial.print("something");

   // delay(250);
   // alternate = !alternate;

    if (Serial.available() > 0) {
      char temp[100];
      int bytes_read = Serial.readBytesUntil('\n', temp, 99);
      temp[bytes_read] = '\0';
      if (temp[0] == '#') {
        color = strtol(temp+1, NULL, 16);
        Serial.print("new color:");
        Serial.print(temp+1);
        Serial.print("\n");
        Serial.print(strtol(temp+1, NULL, 16));
        Serial.print("\nred:");
        Serial.print(color.red);
        Serial.print("\ngreen:");
        Serial.print(color.green);
        Serial.print("\nblue:");
        Serial.print(color.blue);
        Serial.print("\n");
      } else if(temp[0] == '+'){
        textSize = !textSize;
      }else {
        for (int i = 0; i <= strlen(temp); i++) {
         message[i] = toupper(temp[i]);
        }
      }
    }
   
    //blacklist
    char output[sizeof(message)/sizeof(*message)];
      for (int k = 0; k < sizeof(message)/sizeof(*message); k++) {
        if (output[k]) {
          output[k] = '\0';
        }
      }
      char *split_input = strtok(message, " ");
      while (split_input != NULL) {
          //check BL
         for (int i = 0; i < sizeof(black_list)/sizeof(*black_list)-1; i++) {
          strcpy_P(buffer, (char*)pgm_read_word(&(black_list[i])));
            if (!strcmp((buffer), split_input)) {
              int j = 1;
              while (*(split_input + j + 1)) {
                *(split_input + j) = '*';
                j++;
              }
            }
            for (int l = 0; l <= 99; l++){
              buffer[l] = NULL;
            }
          }
      strcat(output,split_input );
  
      const char *space = " ";
      strcat(output,space );
  
      split_input = strtok(NULL, " ");
    }
  strcpy(message, output);

    // color = rainbowColor(); 
  Serial.print(message);
  Serial.print("\n");
  scrollMessage(1, message, color, textSize);



    // for (int i = 0; i < NUM_LEDS; i++) {
    //   leds[i] = CRGB(0,255,0);
    // }
    FastLED.show();

}
