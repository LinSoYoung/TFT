#include <TFT.h>

uint32_t Math::FastUIntMpy(uint32_t a, uint32_t b) {
    uint32_t o = 0;
    for (uint32_t i = 0; i < b; i++) {
        o += a;
    }
    return o;
}

