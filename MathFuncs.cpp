#include <TFT.h>

namespace Math {
    uint32_t FastUIntMpy(uint32_t a, uint32_t b) {
        uint32_t res;
        asm volatile("multu $a0, $a1");
        asm volatile("mflo %0" :: "r"(res));
        return res;
    }
    uint32_t FastUIntDiv(uint32_t a, uint32_t b) {
        uint32_t res;
        asm volatile("divu $a0, $a1");
        asm volatile("mflo %0" :: "r"(res));
        return res;
    }
    uint32_t Percent(uint32_t val, uint32_t pct) {
        uint32_t res;
        asm volatile("multu $a0, $a1");
        asm volatile("ori $v1, $zero, 100");
        asm volatile("mflo $v0");
        asm volatile("divu $v0, $v1");
        asm volatile("mflo %0" :: "r"(res));
        return res;
    }
}

