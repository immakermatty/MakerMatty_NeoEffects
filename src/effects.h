/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_EFFECTS_h
#define _MM_NEOEFFECTS_EFFECTS_h

#include "effect.h"

NEOEFFECTS_NAMESPACE_BEGIN

class FillEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        fill_solid(frame->leds(), frame->length(), color);
    }

public:
    FillEffect(time_ms duration, CRGB color)
        : Effect(duration)
        , color(color) {};

private:
    CRGB color;
};

/////////////////////////////////////////////////////////////////////////////////////////

class RainbowEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        CRGB* leds = frame->leds();
        int32_t len = frame->length();

        uint8_t palletteIndex = tmap(time, 0, duration - 1, 0, UINT8_MAX / 2);

        for (int i = 0; i < len; i++) {
            leds[i] = ColorFromPalette(RainbowColors_p, palletteIndex * 2, 0xFF, LINEARBLEND);
            palletteIndex++;
        }
    }

public:
    RainbowEffect(time_ms duration = 1000)
        : Effect(duration) {};
};

/////////////////////////////////////////////////////////////////////////////////////////

class PlasmaShotEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        CRGB* leds = frame->leds();
        int32_t len = frame->length();

        int32_t neopixelIndex = tmap(time, 0, duration - 1, 0, frame->length() - 1);

        for (int32_t i = 0; i < len; i++) {

            CRGB c = color;
            uint8_t scale = (uint8_t)tmap(tabs(i - neopixelIndex), 0, (int)count, 255, 0);
            c.nscale8(scale);

            leds[i] = c;
        }
    }

public:
    PlasmaShotEffect(time_ms duration = 500, CRGB color = CRGB::White, int32_t count = 5)
        : Effect(duration)
        , color(color)
        , count(count) {};

private:
    CRGB color;
    int32_t count;
};

/////////////////////////////////////////////////////////////////////////////////////////

class LoadingBarEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        CRGB* leds = frame->leds();
        int32_t len = frame->length();

        int32_t count = tmap(time, 0, duration - 1, 0, len - 1);

        fill_solid(&leds[0], count, color1);
        fill_solid(&leds[count], len - count, color2);
    }

public:
    LoadingBarEffect(time_ms duration = 1000, CRGB color1 = CRGB::Green, CRGB color2 = CRGB::Black)
        : Effect(duration)
        , color1(color1)
        , color2(color2) {};

private:
    CRGB color1;
    CRGB color2;
};

/////////////////////////////////////////////////////////////////////////////////////////

class FadeEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        uint8_t ratio = (uint8_t)tmap(time, 0, duration - 1, 0x00, 0xFF);

        CRGB c1 = color1;
        CRGB c2 = color2;

        CRGB c = c1.nscale8(255 - ratio) + c2.nscale8(ratio);

        fill_solid(frame->leds(), frame->length(), c);
    }

public:
    FadeEffect(time_ms duration = 1000, CRGB color1 = CRGB::Black, CRGB color2 = CRGB::White)
        : Effect(duration)
        , color1(color1)
        , color2(color2) {};

private:
    CRGB color1;
    CRGB color2;
};

///////////////////////////////////////////////////////////////////////////////////////////

class RollEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        CRGB* leds = frame->leds();
        int32_t len = frame->length();

        int32_t offset = tmap(time, 0, duration - 1, 0, len * 2);

        for (int32_t i = 0; i < len; i++) {
            double angle = (double)map(i + offset, 0, len, 0, (long)(TWO_PI * 1000000L)) / 1000000.0;

            uint8_t fraction = ((cos(angle) + 1.0) / 2.0) * 255;
            leds[i] = blend(color1, color2, fraction);
        }
    }

public:
    RollEffect(time_ms duration = 1000, CRGB color1 = CRGB::Black, CRGB color2 = CRGB::White)
        : Effect(duration)
        , color1(color1)
        , color2(color2) {};

private:
    CRGB color1;
    CRGB color2;
};

///////////////////////////////////////////////////////////////////////////////////////////

class PaletteRollEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        CRGB* leds = frame->leds();
        int32_t len = frame->length();

        uint8_t index = tmap(time, 0, duration - 1, 0x00, 0xFF);

        for (int i = 0; i < len; i++) {
            leds[i] = ColorFromPalette(palette, index, 0xFF, blend);
            index++;
        }
    }

public:
    PaletteRollEffect(time_ms duration, CRGBPalette16& pallette, TBlendType blend = LINEARBLEND)
        : Effect(duration)
        , palette(pallette)
        , blend(blend) {};

private:
    CRGBPalette16 palette;
    TBlendType blend;
};

NEOEFFECTS_NAMESPACE_END

#endif
#endif