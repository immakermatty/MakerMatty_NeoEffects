/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_FRAME_h
#define _MM_NEOEFFECTS_FRAME_h

#include <Arduino.h>
#include "config.h"
#define FASTLED_INTERNAL
#include <FastLED.h>

NEOEFFECTS_NAMESPACE_BEGIN

class Neopixels {
public:
    Neopixels(int32_t neopixelCount, bool clear = true, bool reversed = false);
    Neopixels(const Neopixels& neopixels); //copy constructor

    ~Neopixels();

    void clear();
    void fill(CRGB color);
    void copy(Neopixels* other, int32_t offset = 0);
    void reverse();

    void setExternalBuffer(CRGB* buffer, int32_t length);
    
    const int32_t length() const { return length_; }; //getter
    CRGB* leds() const { return leds_; }; //getter

    Neopixels& operator=(const Neopixels& other);
    void swap(Neopixels& other) throw(/* throws nothing */);

private:
    int32_t length_;
    CRGB* leds_;
    bool reversed_;
    bool allocated_;
};

typedef Neopixels Frame;

NEOEFFECTS_NAMESPACE_END

#endif
#endif