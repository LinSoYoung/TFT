#include <TFT.h>

namespace Math {
    uint32_t FastUIntMpy(uint16_t a, uint16_t b) {
        uint32_t o = 0;

        for (int i = 0; i < 16; i++) {
            if ((b & (1<<i)) != 0) {
                o += (a << i);
            }
        }
        return o;
    }
}

