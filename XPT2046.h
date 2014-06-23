#ifndef _XPT2046_H
#define _XPT2046_H

#include <TFT.h>

class XPT2046 : public Touch {
    public: 
        XPT2046(TFTCommunicator *comm, uint16_t w, uint16_t h) : Touch(comm, w, h) {}
        XPT2046(TFTCommunicator &comm, uint16_t w, uint16_t h) : Touch(comm, w, h) {}

        void sample();
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

        void setRotation(uint8_t r);

    private:
        struct coord pos;
        boolean pressed;
        uint8_t _rotation;
};

#endif

