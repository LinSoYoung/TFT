#ifndef _MATH_H
#define _MATH_H

#include <TFT.h>

namespace Math {
    extern uint32_t FastUIntMpy(uint32_t a, uint32_t b);
    extern uint32_t FastUIntDiv(uint32_t a, uint32_t b);
    extern uint32_t Percent(uint32_t val, uint32_t pct);
};

#endif
