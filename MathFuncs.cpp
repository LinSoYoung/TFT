#include <TFT.h>

namespace Math {
    uint32_t FastUIntMpy(uint16_t a, uint16_t b) {
        uint32_t res;
        asm volatile("multu $a0, $a1");
        asm volatile("mflo %0" :: "r"(res));
        return res;
    }
}

