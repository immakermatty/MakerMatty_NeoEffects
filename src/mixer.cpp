#ifdef ESP32

#include "mixer.h"

NEOEFFECTS_NAMESPACE_BEGIN

namespace Mixer {

Frame* set(Frame* src, Frame* f)
{
    if (f == nullptr) {
        return src;
    }

    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), f->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i] = f->leds()[i];
    }

    return src;
}

Frame* add(Frame* src, Frame* f)
{
    if (f == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), f->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i] += f->leds()[i];
    }

    return src;
}

Frame* mask(Frame* src, Frame* msk)
{
    if (msk == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), msk->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i] &= msk->leds()[i];
    }

    return src;
}

Frame* mask(Frame* src, uint8_t msk)
{
    if (src == nullptr) {
        return nullptr;
    }

    for (int32_t i = 0; i < src->length(); i++) {
        src->leds()[i] &= msk;
    }

    return src;
}

Frame* scale(Frame* src, Frame* msk)
{
    if (msk == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), msk->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i].nscale8(msk->leds()[i]);
    }

    return src;
}

Frame* scale(Frame* src, uint8_t msk)
{
    if (src == nullptr) {
        return nullptr;
    }

    for (int32_t i = 0; i < src->length(); i++) {
        src->leds()[i].nscale8(msk);
    }

    return src;
}

}

NEOEFFECTS_NAMESPACE_END

#endif