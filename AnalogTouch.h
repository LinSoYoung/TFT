#ifndef _ANALOGTOUCH_H
#define _ANALOGTOUCH_H

#include <TFT.h>

class AnalogTouch : public Touch {
    public: 
        AnalogTouch(uint8_t xl, uint8_t xr, uint8_t yu, uint8_t yd, uint16_t w, uint16_t h) : Touch(w, h), 
            _xl(xl), _xr(xr), _yu(yu), _yd(yd) {}

        void sample();
        int getSample(uint8_t);
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

        void scaleX(float v);
        void scaleY(float v);

        uint16_t pressure();

    private:
        struct coord _pos;
        boolean _pressed;
        uint8_t _yu;
        uint8_t _yd;
        uint8_t _xl;
        uint8_t _xr;
        float _scale_x;
        float _scale_y;
        uint16_t _pressure;
};

#endif

