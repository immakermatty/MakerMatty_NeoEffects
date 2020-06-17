/** 
 * Author	: @makermatty (maker.matejsuchanek.cz)
 * Date		: 15-6-2020
 */

#ifdef ESP32

#ifndef _MM_NEOEFFECTS_MIXER_h
#define _MM_NEOEFFECTS_MIXER_h

#include "frame.h"

NEOEFFECTS_NAMESPACE_BEGIN

namespace Mixer {

typedef Frame* (*FrCombFunc)(Frame* src, Frame* frame);

Frame* set(Frame* src, Frame* add);
Frame* add(Frame* src, Frame* add);
Frame* mask(Frame* src, Frame* msk);
Frame* mask(Frame* src, uint8_t msk);
Frame* scale(Frame* src, Frame* msk);
Frame* scale(Frame* src, uint8_t msk);

}

NEOEFFECTS_NAMESPACE_END

#endif
#endif