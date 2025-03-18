#pragma once

#include "quantum.h"


typedef struct Carousel {
    uint16_t keycode;
    char * options;
} Carousel;
const Carousel PROGMEM carousels[CAROUSEL_MAX];
bool process_carousel(uint16_t keycode, keyrecord_t *record);