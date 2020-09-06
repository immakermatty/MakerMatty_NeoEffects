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

typedef Frame* (*DrawFunc)(Frame* src, const Frame* msk);

// @brief Set msk frame to src frame
Frame* set(Frame* src, const Frame* msk);

// @brief Add frame to another frame
Frame* add(Frame* src, const Frame* msk);

// @brief Filter frame by another frame
Frame* sub(Frame* src, const Frame* msk);

// @brief Filter frame by another frame
Frame* mul(Frame* src, const Frame* msk);

// @brief Filter frame by another frame
Frame* fil(Frame* src, const Frame* msk);

}

NEOEFFECTS_NAMESPACE_END

#endif
#endif