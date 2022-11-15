#include <Arduino.h>
#include <ArduinoBLE.h>
#include "LEDController.h"
#include "BLE.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

static const char *TAG = "main.cpp";

CRGB gLeds[NUM_LEDS];

u_int8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
u_int8_t gBrightnessLevel = BRIGHTNESS;

u_int8_t gHue = 0; // rotating "base color" used by many of the patterns
SimplePatternList gPatterns = {rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm};

void setup() {
	Serial.begin(115200);
	Serial.println("ESP32 Started!");

	delay(2000); // 3 seconds delay for recovery
	Serial.printf("Init FastLED... DATA_PIN[%d], NUM_LEDS[%d], BRIGHTNESS[%d/255 (%d%%)]\n", DATA_PIN, NUM_LEDS,
				  BRIGHTNESS, BRIGHTNESS * 100 / 255);
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(gLeds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);

	// Init Bluetooth device.
	initBluetoothServer();
}

void nextPattern() {
	// add one to the current pattern number, and wrap around at the end
	gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void loop() {
	BLE.poll();

	gPatterns[gCurrentPatternNumber]();

	// send the 'leds' array out to the actual LED strip
	FastLED.show();
	// insert a delay to keep the framerate modest
	FastLED.delay(1000 / FRAMES_PER_SECOND);

	// do some periodic updates
	EVERY_N_MILLISECONDS(20) { gHue++; } // slowly cycle the "base color" through the rainbow
//	EVERY_N_SECONDS(10) { nextPattern(); } // change patterns periodically
}