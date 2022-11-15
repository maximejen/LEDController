#include "LEDController.h"

extern CRGB gLeds[NUM_LEDS];
extern uint8_t gCurrentPatternNumber;
extern uint8_t gHue;
extern SimplePatternList gPatterns;

void rainbow() {
	// FastLED's built-in rainbow generator
	fill_rainbow(gLeds, NUM_LEDS, gHue, 7);
}

void addGlitter(fract8 chanceOfGlitter) {
	if (random8() < chanceOfGlitter) {
		gLeds[random16(NUM_LEDS)] += CRGB::White;
	}
}

void rainbowWithGlitter() {
	// built-in FastLED rainbow, plus some random sparkly glitter
	rainbow();
	addGlitter(80);
}

void confetti() {
	// random colored speckles that blink in and fade smoothly
	fadeToBlackBy(gLeds, NUM_LEDS, 10);
	int pos = random16(NUM_LEDS);
	gLeds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon() {
	// a colored dot sweeping back and forth, with fading trails
	fadeToBlackBy(gLeds, NUM_LEDS, 20);
	int pos = beatsin16(13, 0, NUM_LEDS - 1);
	gLeds[pos] += CHSV(gHue, 255, 192);
}

void bpm() {
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t BeatsPerMinute = 62;
	CRGBPalette16 palette = PartyColors_p;
	uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
	for (int i = 0; i < NUM_LEDS; i++) { //9948
		gLeds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
	}
}

void juggle() {
	// eight colored dots, weaving in and out of sync with each other
	fadeToBlackBy(gLeds, NUM_LEDS, 20);
	byte dotHue = 0;
	for (int i = 0; i < 8; i++) {
		gLeds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dotHue, 200, 255);
		dotHue += 32;
	}
}