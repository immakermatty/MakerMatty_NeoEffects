// #ifdef ESP32

// #include "sequence.h"

// NEOEFFECTS_NAMESPACE_BEGIN

// Sequence::Sequence(uint16_t count)
//     : effects_(new Effect*[count])
//     , effectsSize_(count)
//     , effectsCount_(0)
//     , effectsIndex_(0)
//     , effectsDuration_(0)
// {
// }

// Sequence::Sequence(const Sequence& other)
//     : effects_(new Effect*[other.effectsCount_])
//     , effectsSize_(other.effectsSize_)
//     , effectsCount_(other.effectsCount_)
//     , effectsIndex_(other.effectsIndex_)
//     , effectsDuration_(other.effectsDuration_)
// {
//     memcpy(effects_, other.effects_, other.effectsCount_);
// }

// void Sequence::add(Effect* const effect)
// {
//     if (effectsCount_ >= effectsSize_) {
//         assert(effectsCount_ < effectsSize_);
//         return;
//     }

//     effects_[effectsCount_++] = effect;

//     effectsDuration_ += effect->duration();
//     if (effectsDuration_ < 0) { //overflow
//         effectsDuration_ = TIME_MS_MAX;
//     }
// }

// bool Sequence::at(time_ms time, Frame* const frame)
// {
//     if (time > effectsDuration_) {
//         return false;
//     }

//     // //rework this to use effectsIndex_ to be constant time
//     // for (size_t i = 0; i < effectsCount_; i++) {
//     //     if (time >= effects_[i]->duration()) {
//     //         time -= effects_[i]->duration();
//     //     } else {

//     //         return effects_[i]->at(time, frame);
//     //     }
//     // }

//     //rework this to use effectsIndex_ to be constant time
//     for (size_t i = 0; i < effectsCount_; i++) {
//         if (effects_[i]->at(time, frame)) {
//             return true;
//         } else {
//             time -= effects_[i]->duration();
//         }
//     }

//     assert(0); //is the loop got here, something is wrong
//     return false;
// }

// Sequence& Sequence::operator=(const Sequence& other)
// {
//     if (this != &other) {
//         Sequence(other).swap(*this); //Copy-constructor and non-throwing swap
//     }

//     // Old resources are released with the destruction of the temporary above
//     return *this;
// }

// void Sequence::swap(Sequence& other) throw(/* throwing nothing */) // Also see non-throwing swap idiom
// {
//     std::swap(this->effects_, other.effects_);
//     std::swap(this->effectsSize_, other.effectsSize_);
//     std::swap(this->effectsCount_, other.effectsCount_);
//     std::swap(this->effectsIndex_, other.effectsIndex_);
//     std::swap(this->effectsDuration_, other.effectsDuration_);
// }

// Sequence::~Sequence()
// {
//     delete[] effects_;
// }

// NEOEFFECTS_NAMESPACE_END

// #endif