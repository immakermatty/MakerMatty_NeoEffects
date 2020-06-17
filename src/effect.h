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

    /* getter */ inline const bool reversed() const { return duration_ < 0 ? true : false; };
    /* getter */ inline const time_ms duration() const { return abs(duration_); } //getter

protected:
    virtual void onAt(time_ms time, time_ms duration, Frame* const frame) = 0;

private:
    time_ms duration_;
};

NEOEFFECTS_NAMESPACE_END

#endif
#endif