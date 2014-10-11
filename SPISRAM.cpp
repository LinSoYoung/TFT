#include <TFT.h>

#define RAMSPEED 10000000UL

uint8_t SPISRAM::xfer(uint8_t d) {
    return _dspi->transfer(d);
}

void SPISRAM::setSpeed() {
    return _dspi->setSpeed(RAMSPEED);
}

void SPISRAM::initializeDevice() {
    _dspi->begin();
    setSpeed();
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

uint8_t SPISRAM::read8(uint32_t address) {
    uint8_t b;  
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    b = xfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

uint16_t SPISRAM::read16(uint32_t address) {
    uint16_t b;  
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    b = xfer(0x00) << 8;
    b |= xfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

uint32_t SPISRAM::read32(uint32_t address) {
    uint32_t b;  
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    b = xfer(0x00) << 24;
    b |= xfer(0x00) << 16;
    b |= xfer(0x00) << 8;
    b |= xfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

void SPISRAM::read8(uint32_t address, uint8_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = xfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::read16(uint32_t address, uint16_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = xfer(0x00) << 8;
        b[i] |= xfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::read32(uint32_t address, uint32_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x03);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = xfer(0x00) << 24;
        b[i] |= xfer(0x00) << 16;
        b[i] |= xfer(0x00) << 8;
        b[i] |= xfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write8(uint32_t address, uint8_t b) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    xfer(b);
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write16(uint32_t address, uint16_t b) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    xfer((b >> 8) & 0xFF);
    xfer(b & 0xFF);
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write32(uint32_t address, uint32_t b) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    xfer((b >> 24) & 0xFF);
    xfer((b >> 16) & 0xFF);
    xfer((b >> 8) & 0xFF);
    xfer(b & 0xFF);
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write8(uint32_t address, uint8_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        xfer(b[i]);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write16(uint32_t address, uint16_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        xfer((b[i] >> 8) & 0xFF);
        xfer(b[i] & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::write32(uint32_t address, uint32_t *b, uint32_t len) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer((address >> 16) & 0xFF);
    xfer((address >> 8) & 0xFF);
    xfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        xfer((b[i] >> 24) & 0xFF);
        xfer((b[i] >> 16) & 0xFF);
        xfer((b[i] >> 8) & 0xFF);
        xfer(b[i] & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::setAll8(uint8_t data) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer(0);
    xfer(0);
    xfer(0);
    for (uint32_t i = 0; i < _size; i++) {
        xfer(data);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::setAll16(uint16_t data) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer(0);
    xfer(0);
    xfer(0);
    for (uint32_t i = 0; i < _size; i+=2) {
        xfer((data >> 8) & 0xFF);
        xfer(data & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}

void SPISRAM::setAll32(uint32_t data) {
    setSpeed();
    digitalWrite(_cs, LOW);
    xfer(0x02);
    xfer(0);
    xfer(0);
    xfer(0);
    for (uint32_t i = 0; i < _size; i+=4) {
        xfer((data >> 24) & 0xFF);
        xfer((data >> 16) & 0xFF);
        xfer((data >> 8) & 0xFF);
        xfer(data & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}

