/*
** LEDController.h
**
** Made by Maxime JENNY
*/

#ifndef LED_CONTROLLER_H_
# define LED_CONTROLLER_H_

# include "FastLED.h"

# define DATA_PIN    13
# define LED_TYPE    WS2812
# define COLOR_ORDER RGB
# define NUM_LEDS    60

# define BRIGHTNESS          15
# define FRAMES_PER_SECOND  120

# define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

typedef void (*SimplePatternList[])();

// ledPatterns.cpp
void rainbow();

void rainbowWithGlitter();

void confetti();

void sinelon();

void juggle();

void bpm();


#endif /* LED_CONTROLLER_H_ */
