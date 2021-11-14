#define FASTLED_INTERNAL
#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    60
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

uint8_t r[] = {66,  66,   8,  33,   8,  66,  66,  66,  33, 158, 107,  33,  33,
        66,   8,  66,  66,  33,  33,   8,   8,  66,  33, 107,  66, 107,
       107, 107, 158, 198, 198, 222, 198, 158, 198, 107, 198, 222, 158,
       198, 158, 158, 158, 222, 222, 222, 252, 254, 252, 251, 251, 239,
       239, 239, 239, 103, 165};
uint8_t g[] = {146, 146,  81, 113,  81, 146, 146, 146, 113, 202, 174, 113, 113,
       146,  81, 146, 146, 113, 113,  81,  81, 146, 113, 174, 146, 174,
       174, 174, 202, 219, 219, 235, 219, 202, 219, 174, 219, 235, 202,
       219, 202, 202, 202, 235, 235, 235, 187, 224, 187, 106, 106,  59,
        59,  59,  59,   0,  15};
uint8_t b[] = {198, 198, 156, 181, 156, 198, 198, 198, 181, 225, 214, 181, 181,
       198, 156, 198, 198, 181, 181, 156, 156, 198, 181, 214, 198, 214,
       214, 214, 225, 239, 239, 247, 239, 225, 239, 214, 239, 247, 225,
       239, 225, 225, 225, 247, 247, 247, 161, 210, 161,  74,  74,  44,
        44,  44,  44,  13,  21};





CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette32 myRedWhiteBluePalette;
extern const TProgmemPalette32 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( CRGB(255, 75, 75 ));
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
  
    static uint8_t startIndex = 0;
 //   startIndex = startIndex + 1; /* motion speed */
    
//    FillLEDsFromPaletteColors( startIndex);
    show_warming();
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void show_warming()
{ 
  for( int i = 0; i < 57; ++i) {
    leds[i] = CRGB(r[i], g[i], b[i]);
  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette32 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black,

      CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
