#include <TFT.h>

#define TOUCH_CMD_X        0xD0
#define TOUCH_CMD_Y        0x90

#define XPT2046_SMPSIZE 10

void XPT2046::initializeDevice() {
    _comm->initializeDevice();
    pressed = false;
    pos.x = 0;
    pos.y = 0;
    _rotation = 0;
}

uint16_t XPT2046::x() {
    int x = pos.x * _width / 4096;
    int y = pos.y * _height / 4096;

    switch (_rotation) {
        case 0:
            return x;
        case 3:
            return _height - y;
        case 2:
            return _width - x;
        case 1:
            return y;
    }
    return 0;
}

uint16_t XPT2046::y() {
    int x = pos.x * _width / 4096;
    int y = pos.y * _height / 4096;

    switch (_rotation) {
        case 0:
            return y;
        case 3:
            return x;
        case 2:
            return _height - y;
        case 1:
            return _width - x;
    }
    return 0;
}


boolean XPT2046::isPressed() {
    return pressed;
}

void XPT2046::sample() {

    uint32_t temp;

    struct coord tpos;
    temp = 0;
    for (uint8_t i = 0; i < XPT2046_SMPSIZE; i++) {
        _comm->streamStart();
        _comm->streamCommand8(TOUCH_CMD_X);
        temp += _comm->streamCommand16() >> 3;
        _comm->streamEnd();
    }
    pos.x = temp / XPT2046_SMPSIZE;
    temp = 0;
    for (uint8_t i = 0; i < XPT2046_SMPSIZE; i++) {
        _comm->streamStart();
        _comm->streamCommand8(TOUCH_CMD_Y);
        temp += _comm->streamCommand16() >> 3;
        _comm->streamEnd();
    }
    pos.y = 4095-(temp / XPT2046_SMPSIZE);

    if ((pos.x >= 4095) || (pos.y >= 4095) || (pos.x == 0) || (pos.y == 0)) {
        pressed = 0;
        return;
    }
    
    pressed = 1;
}

void XPT2046::setRotation(uint8_t r) {
    _rotation = r % 4;
}

