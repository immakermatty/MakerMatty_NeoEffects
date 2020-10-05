#ifdef ESP32

#include "effect.h"

NEOEFFECTS_NAMESPACE_BEGIN

Effect::Effect(const time_ms duration)
    :next_(nullptr) 
    , duration_(duration)
{
}

bool Effect::at(const time_ms time, Frame* const frame)
{
    assert(frame != nullptr);

    if (time < 0) {
        return true;
    }

    time_ms duration = abs(duration_);

    if (time < duration) {
        if (frame == nullptr) {
            return true;
        }
        onAt(duration_ < 0 ? duration - time - 1 : time, duration, frame);
        return true;
    } else {
        if (next_ != nullptr) {
            return next_->at(time - duration, frame);
        } else {
            return false;
        }
    }
}

time_ms Effect::untilEnd(const time_ms time)
{
    return abs(duration_) - time;
}

 time_ms Effect::duration() const
{
    if (next_ != nullptr) {
        return next_->duration() + abs(duration_);
    } else {
        return abs(duration_);
    }
}

 bool Effect::reversed() const
{
    return duration_ < 0 ? true : false;
}

Effect::~Effect()
{
    if (next_) {
        delete next_;
    }
};

NEOEFFECTS_NAMESPACE_END

#endif