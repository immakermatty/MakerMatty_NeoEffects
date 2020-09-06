/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_FRAME_h
#define _MM_NEOEFFECTS_FRAME_h

#include "config.h"
#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <functional>

NEOEFFECTS_NAMESPACE_BEGIN

class Neopixels {

public:
    enum DrawMode : uint8_t {
        SET,
        ADD,
        SUB,
        FILTER,
        //BLUR
    };

public:
    Neopixels(int32_t neopixelCount, bool clear = true, bool reversed = false);
    Neopixels(const Neopixels& neopixels); //copy constructor

    ~Neopixels();

    void setExternalBuffer(CRGB* buffer, int32_t length);

    void clear();
    void fill(CRGB color);
    void copy(Neopixels* other, int32_t offset = 0);
    void reverse();

    void setDrawMode(DrawMode mode);
    void draw(int32_t index, const CRGB& color);

    Neopixels& operator=(const Neopixels& other);

    CRGB& operator[](std::size_t idx);
    const CRGB& operator[](std::size_t idx) const;

    const int32_t length() const { return length_; }; //getter
    CRGB* leds() const { return leds_; }; //getter

private:
    void swap(Neopixels& other) throw(/* throws nothing */);

private:
    int32_t length_;
    CRGB* leds_;
    DrawMode mode_;

    bool reversed_;
    bool allocated_;
};

typedef Neopixels Frame;

NEOEFFECTS_NAMESPACE_END

#endif
#endif