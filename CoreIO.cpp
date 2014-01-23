#include <TFT.h>

uint16_t CoreIO::pins() {
    return NUM_DIGITAL_PINS;
}

void CoreIO::digitalWrite(uint16_t pin, uint8_t val) {
    ::digitalWrite(pin, val);
}

uint8_t CoreIO::digitalRead(uint16_t pin) {
    return ::digitalRead(pin);
}

void CoreIO::pinMode(uint16_t pin, uint8_t mode) {
    ::pinMode(pin, mode);
}

void CoreIO::startBuffer() {
}

void CoreIO::endBuffer() {
}
