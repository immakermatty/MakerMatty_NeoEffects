#ifdef ESP32

#include "frame.h"

NEOEFFECTS_NAMESPACE_BEGIN

Neopixels::Neopixels(const int32_t len, bool clr, bool rever)
    : length_(len)
    , leds_(new CRGB[length_])
    , reversed_(rever)
    , allocated_(true)
{
    assert(length_ >= 0);
    assert(leds_ != nullptr);

    if (clr) {
        clear();
    }
}

Neopixels::Neopixels(const Neopixels& other)
    : length_(other.length_)
    , leds_(other.allocated_ ? new CRGB[length_] : other.leds_)
    , reversed_(other.reversed_)
    , allocated_(other.allocated_)
{
    assert(length_ >= 0);
    assert(leds_ != nullptr);

    if (allocated_) {
        memcpy(leds_, other.leds_, other.length_);
    }
}

void Neopixels::clear()
{
    fill(CRGB::Black);
}

void Neopixels::fill(CRGB color)
{
    fill_solid(leds_, length_, color);
}

void Neopixels::copy(Neopixels* other, int32_t offset)
{
    if (other == nullptr)
        return;

     if (offset >= other->length_)
        return;

    int32_t len = min(other->length_ - offset, length_);
    for (int32_t i = 0; i < len; i++) {
        if (!reversed_) {
            leds_[i] = other->leds_[i + offset];
        } else {
            leds_[len - i - 1] = other->leds_[i + offset];
        }
    }
}

void Neopixels::reverse()
{
    std::reverse(leds_, leds_ + length_);
}

void Neopixels::setExternalBuffer(CRGB* buffer, int32_t len)
{
    if (allocated_) {
        delete[] leds_;
        allocated_ = false;
    }

    leds_ = buffer;
    length_ = len;
}

Neopixels& Neopixels::operator=(const Neopixels& other)
{
    if (this != &other) {
        Neopixels(other).swap(*this); //Copy-constructor and non-throwing swap
    }

    // Old resources are released with the destruction of the temporary above
    return *this;
}

void Neopixels::swap(Neopixels& other) throw(/* throwing nothing */) // Also see non-throwing swap idiom
{
    std::swap(this->length_, other.length_);
    std::swap(this->leds_, other.leds_);
    std::swap(this->reversed_, other.reversed_);
    std::swap(this->allocated_, other.allocated_);
}

Neopixels::~Neopixels()
{
    if (allocated_) {
        delete[] leds_;
    }
};

NEOEFFECTS_NAMESPACE_END

#endif