#include <TFT.h>

#define ANALOGTOUCH_SMPSIZE 10

void AnalogTouch::initializeDevice() {
    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    _pos.x = 0;
    _pos.y = 0;
    _pressed = false;
    _scale_x = 1900 / (_width);
    _scale_y = 1700 / (_height);
}

uint16_t AnalogTouch::x() {
    return _pos.x;
}

uint16_t AnalogTouch::y() {
    return _pos.y;
}

boolean AnalogTouch::isPressed() {
    return _pressed;
}

int AnalogTouch::getSample(uint8_t pin) {
    int thisSample = 0;
    for (int i = 0; i < ANALOGTOUCH_SMPSIZE; i++) {
        thisSample += analogRead(pin);
    }
    return thisSample/ANALOGTOUCH_SMPSIZE;
}

#if !defined(max)
#define max(A,B) ((A) > (B) ? (A) : (B))
#endif

void AnalogTouch::sample() {
    pinMode(_xl, OUTPUT);
    pinMode(_xr, OUTPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    digitalWrite(_xl, LOW);
    digitalWrite(_xr, HIGH);
    int x1 = getSample(_yu);

    pinMode(_xl, OUTPUT);
    pinMode(_xr, OUTPUT);
    pinMode(_yu, INPUT);
    pinMode(_yd, INPUT);
    digitalWrite(_xl, HIGH);
    digitalWrite(_xr, LOW);
    int x2 = getSample(_yu);

    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, OUTPUT);
    pinMode(_yd, OUTPUT);
    digitalWrite(_yu, LOW);
    digitalWrite(_yd, HIGH);
    int y1 = getSample(_xl);

    pinMode(_xl, INPUT);
    pinMode(_xr, INPUT);
    pinMode(_yu, OUTPUT);
    pinMode(_yd, OUTPUT);
    digitalWrite(_yu, HIGH);
    digitalWrite(_yd, LOW);
    int y2 = getSample(_xl);

    _pressed = false;
    if (
        (x1 >= 10) &&
        (y1 >= 10) &&
        (x2 >= 10) &&
        (y2 >= 10) &&
        (x1 < 1000) &&
        (x2 < 1000) &&
        (y1 < 1000) &&
        (y2 < 1000) 
    ) {
        if (abs(x1 - x2) < 900 && abs(y1 - y2) < 900) {
            _pressed = true;
            _pos.x = (_width / 2) + ((x1 - x2) / _scale_x);
            _pos.y = (_height / 2) + ((y1 - y2) / _scale_y);
        }
    }

    _pressure = max(abs(x1 - x2), abs(y1 - y2));
}

void AnalogTouch::scaleX(float v) {
    _scale_x = v;
}

void AnalogTouch::scaleY(float v) {
    _scale_y = v;
}

uint16_t AnalogTouch::pressure() {
    return _pressure;
}
