#ifndef _CORE_IO
#define _CORE_IO

#include <TFT.h>

#include <Board_Defs.h>

class CoreIO : public ParallelIO {
    public:
        uint16_t pins();
        void digitalWrite(uint16_t pin, uint8_t val);
        uint8_t digitalRead(uint16_t pin);
        void pinMode(uint16_t pin, uint8_t mode);
        void startBuffer();
        void endBuffer();
};

#endif
