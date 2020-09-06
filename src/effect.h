/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_EFFECT_h
#define _MM_NEOEFFECTS_EFFECT_h

#include "MakerMatty_TemplateMath.h"
#include "MakerMatty_TimeTrack.h"
#include "frame.h"

NEOEFFECTS_NAMESPACE_BEGIN

class Effect {
public:
    Effect(const time_ms duration = TIME_MS_MAX);
    virtual ~Effect();

    bool at(const time_ms time, Frame* const frame);
    time_ms untilEnd(const time_ms time);

    Effect* next() const { return next_; };
    void next(Effect* value) { next_ = std::move(value); };

    bool reversed() const;
    time_ms duration() const;

protected:
    virtual void onAt(time_ms time, time_ms duration, Frame* const frame) = 0;

private:
    Effect* next_;
    time_ms duration_;

    void updateDuration();
};

NEOEFFECTS_NAMESPACE_END

#endif
#endif