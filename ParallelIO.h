#ifndef _PARALLEL_IO
#define _PARALLEL_IO

#include <TFT.h>

class ParallelIO {
    public:
        virtual void digitalWrite(uint16_t pin, uint8_t value) = 0;
        virtual uint8_t digitalRead(uint16_t pin) = 0;
        virtual void pinMode(uint16_t pin, uint8_t mode) = 0;
        virtual uint16_t pins() = 0;
        virtual void startBuffer() = 0;
        virtual void endBuffer() = 0;
};

#endif
