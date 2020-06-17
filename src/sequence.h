/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_EFFECT_SEQUENCE_h
#define _MM_NEOEFFECTS_EFFECT_SEQUENCE_h

#include "effect.h"

NEOEFFECTS_NAMESPACE_BEGIN

// @brief Sequence of Effects, that get played one after the other
class Sequence {
public:
    Sequence(uint16_t count);
    Sequence(const Sequence& other);
    ~Sequence();

    void add(Effect* const effect);
    bool at(time_ms time, Frame* const frame);

    inline const time_ms& duration() const { return effectsDuration_; };

    Sequence& operator=(const Sequence& other);
    void swap(Sequence& other) throw(/* throws nothing */);

private:
    Effect** effects_;
    uint16_t effectsSize_;
    uint16_t effectsCount_;
    uint16_t effectsIndex_;
    time_ms effectsDuration_;
};

NEOEFFECTS_NAMESPACE_END

#endif
#endif