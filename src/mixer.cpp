#ifdef ESP32

#include "mixer.h"

NEOEFFECTS_NAMESPACE_BEGIN

namespace Mixer {

Frame* set(Frame* src, const Frame* f)
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

Frame* add(Frame* src, const Frame* f)
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

Frame* sub(Frame* src, const Frame* f)
{
    if (f == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), f->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i] -= f->leds()[i];
    }

    return src;
}

Frame* mul(Frame* src, const Frame* f)
{
    if (f == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), f->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i].nscale8(f->leds()[i]);
    }

    return src;
}

Frame* fil(Frame* src, const Frame* f)
{
    if (f == nullptr) {
        return src;
    }
    if (src == nullptr) {
        return nullptr;
    }

    int32_t len = min(src->length(), f->length());
    for (int32_t i = 0; i < len; i++) {
        src->leds()[i] &= f->leds()[i];
    }

    return src;
}

}

NEOEFFECTS_NAMESPACE_END

#endif