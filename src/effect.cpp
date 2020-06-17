#ifdef ESP32

#include "effect.h"

NEOEFFECTS_NAMESPACE_BEGIN

Effect::Effect(const time_ms duration)
    : duration_(duration)
{
}

bool Effect::at(const time_ms time, Frame* const frame)
{
    assert(frame != nullptr);

    if (time < 0) {
        return true;
    }

    if (time >= abs(duration_)) {
        return false;
    }

    if (frame == nullptr) {
        return true;
    }

    onAt(duration_ < 0 ? -duration_ - time - 1 : time, abs(duration_), frame);
    return true;
}

time_ms Effect::untilEnd(const time_ms time)
{
    return abs(duration_) - time;
}

Effect::~Effect() {};

NEOEFFECTS_NAMESPACE_END

#endif