/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_EFFECTS_h
#define _MM_NEOEFFECTS_EFFECTS_h

#include "effect.h"

NEOEFFECTS_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////////////////

class NoneEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        // NOP
    }

public:
    NoneEffect(time_ms duration)
        : Effect(duration) {};
};

///////////////////////////////////////////////////////////////////////////////////////////

class FillEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        const int32_t length = frame->length();

        for (int32_t i = 0; i < length; i++) {
            frame->draw(i, color);
        }
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
        const int32_t length = frame->length();

        uint8_t palletteIndex = tmap(time, 0, duration - 1, 0, UINT8_MAX);

        for (int i = 0; i < length; i++) {
            uint8_t delta = tmap<int32_t>(i, 0, length, 0, 255 - zoom);
            frame->draw(i, ColorFromPalette(RainbowColors_p, palletteIndex + delta, 0xFF, LINEARBLEND));
        }
    }

public:
    RainbowEffect(time_ms duration = 1000, uint8_t zoom = 32)
        : Effect(duration)
        , zoom(zoom) {};

private:
    uint8_t zoom;
};

/////////////////////////////////////////////////////////////////////////////////////////

class PlasmaShotEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        const int32_t length = frame->length();

        int32_t count = tmap<int32_t>(percentage, 0, 255, 1, length / 2);
        int32_t neopixelIndex = tmap<int32_t>(time, 0, duration - 1, 0 - count, length - 1 + count);
        
        for (int32_t i = 0; i < length; i++) {

            CRGB c = color;
            int32_t delta = i - neopixelIndex;
            uint8_t scale = tmap<int32_t>(abs(delta), 0, count, 255, 0);
            c.nscale8(scale);

            frame->draw(i, c);
        }
    }

public:
    PlasmaShotEffect(time_ms duration = 1000, CRGB color = CRGB::White, uint8_t percentage = 32)
        : Effect(duration)
        , color(color)
        , percentage(percentage) {};

private:
    CRGB color;
    uint8_t percentage;
};

/////////////////////////////////////////////////////////////////////////////////////////

class LoadingBarEffect : public Effect {
    void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
    {
        const int32_t length = frame->length();

        int32_t count = tmap(time, 0, duration - 1, 0, length);

        for (int32_t i = 0; i < count; i++) {
            frame->draw(i, color1);
        }

        for (int32_t i = count; i < length; i++) {
            frame->draw(i, color2);
        }
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
         const int32_t length = frame->length();

        uint8_t ratio = tmap<int32_t>(time, 0, duration - 1, 0x00, 0xFF);

        CRGB c1 = color1;
        CRGB c2 = color2;

        CRGB c = c1.nscale8(255 - ratio) + c2.nscale8(ratio);

        for (int32_t i = 0; i < length; i++) {
            frame->draw(i, c);
        }
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
        int32_t length = frame->length();
        int32_t offset = tmap<int32_t>(time, 0, duration - 1, 0, length * 2);

        for (int32_t i = 0; i < length; i++) {
            double angle = tmap<double>((i + offset) % (length * 2), 0, length * 2, 0, TWO_PI);
            double fraction = ((cos(angle) + 1.0) / 2.0) * 255;

            frame->draw(i, blend(color1, color2, (fract8)fraction));
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
        int32_t length = frame->length();

        int32_t palletteIndex = tmap(time, 0, duration - 1, 0, UINT8_MAX / 2);

        for (int i = 0; i < length; i++) {
            int32_t delta = tmap<int32_t>(i, 0, length, 0, 255 - zoom);
            frame->draw(i, ColorFromPalette(palette, palletteIndex + delta, 0xFF, blend));
        }
    }

public:
    PaletteRollEffect(time_ms duration, CRGBPalette16& pallette, const uint8_t zoom, TBlendType blend = LINEARBLEND)
        : Effect(duration)
        , palette(pallette)
        , blend(blend)
        , zoom(zoom) {};

private:
    CRGBPalette16 palette;
    TBlendType blend;
    uint8_t zoom;
};

// class PaletteRollEffect : public Effect {
//     void onAt(const time_ms time, const time_ms duration, Frame* const frame) override
//     {
//         int32_t length = frame->length();

//         uint8_t palletteIndex = tmap(time, 0, duration - 1, 0, UINT8_MAX / 2);

//         palletteIndex = palletteIndex - (palletteIndex % 3);

//         for (int i = 0; i < length; i += 3) {
//             uint8_t delta = tmap<uint8_t>(i, 0, length, 0, 255 - zoom);
//             CRGB c = ColorFromPalette(palette, palletteIndex + delta, 0xFF, blend);
//             frame->draw(i, c);
//             frame->draw(i + 1, c);
//             frame->draw(i + 2, c);
//         }
//     }

// public:
//     PaletteRollEffect(time_ms duration, CRGBPalette16& pallette, const uint8_t zoom, TBlendType blend = NOBLEND)
//         : Effect(duration)
//         , palette(pallette)
//         , blend(blend)
//         , zoom(zoom) {};

// private:
//     CRGBPalette16 palette;
//     TBlendType blend;
//     uint8_t zoom;
// };

///////////////////////////////////////////////////////////////////////////////////////////


NEOEFFECTS_NAMESPACE_END

#endif
#endif