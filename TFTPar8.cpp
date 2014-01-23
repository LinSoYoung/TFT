#include <TFT.h>

TFTPar8::TFTPar8(ParallelIO *dev, uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    _dev = dev;
    _cs = cs;
    _dc = dc;
    _clk = clk;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;
    _d4 = d4;
    _d5 = d5;
    _d6 = d6;
    _d7 = d7;

    _dev->pinMode(_cs, OUTPUT);
    _dev->pinMode(_dc, OUTPUT);
    _dev->pinMode(_clk, OUTPUT);
    _dev->pinMode(_d0, OUTPUT);
    _dev->pinMode(_d1, OUTPUT);
    _dev->pinMode(_d2, OUTPUT);
    _dev->pinMode(_d3, OUTPUT);
    _dev->pinMode(_d4, OUTPUT);
    _dev->pinMode(_d5, OUTPUT);
    _dev->pinMode(_d6, OUTPUT);
    _dev->pinMode(_d7, OUTPUT);

    _dev->digitalWrite(_cs, HIGH);
    _dev->digitalWrite(_dc, LOW);
    _dev->digitalWrite(_clk, LOW);
}

void TFTPar8::clock() {
    _dev->digitalWrite(_clk, HIGH);
    //delayMicroseconds(1);
    _dev->digitalWrite(_clk, LOW);
    //delayMicroseconds(1);
}

void TFTPar8::setBus(uint8_t value) {
    _dev->digitalWrite(_d7, value & 0x80);
    _dev->digitalWrite(_d6, value & 0x40);
    _dev->digitalWrite(_d5, value & 0x20);
    _dev->digitalWrite(_d4, value & 0x10);
    _dev->digitalWrite(_d3, value & 0x08);
    _dev->digitalWrite(_d2, value & 0x04);
    _dev->digitalWrite(_d1, value & 0x02);
    _dev->digitalWrite(_d0, value & 0x01);
}

void TFTPar8::writeCommand8(uint8_t command) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    _dev->digitalWrite(_cs, LOW);
    setBus(command);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::writeCommand16(uint16_t command) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    _dev->digitalWrite(_cs, LOW);
    setBus((command >> 8) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(command & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::writeCommand32(uint32_t command) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    _dev->digitalWrite(_cs, LOW);
    setBus((command >> 24) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((command >> 16) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((command >> 8) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(command & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::streamStart() {
    _dev->digitalWrite(_cs, LOW);
}

void TFTPar8::streamEnd() {
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::writeData8(uint8_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    _dev->digitalWrite(_cs, LOW);
    setBus(data);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::writeData16(uint16_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    _dev->digitalWrite(_cs, LOW);
    setBus(data >> 8);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::writeData32(uint32_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    _dev->digitalWrite(_cs, LOW);
    setBus((data >> 24) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((data >> 16) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((data >> 8) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->digitalWrite(_cs, HIGH);
}

void TFTPar8::streamCommand8(uint8_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    setBus(data);
    _dev->endBuffer();
    clock();
}

void TFTPar8::streamCommand16(uint16_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    setBus(data >> 8);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    _dev->endBuffer();
    clock();
}

void TFTPar8::streamCommand32(uint32_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, LOW);
    setBus((data >> 24) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((data >> 16) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((data >> 8) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    _dev->endBuffer();
    clock();
}

void TFTPar8::streamData8(uint8_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    setBus(data);
    _dev->endBuffer();
    clock();
}

void TFTPar8::streamData16(uint16_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    setBus(data >> 8);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    _dev->endBuffer();
    clock();
}

void TFTPar8::streamData32(uint32_t data) {
    _dev->startBuffer();
    _dev->digitalWrite(_dc, HIGH);
    setBus((data >> 24) & 0xFF);
    clock();
    _dev->startBuffer();
    setBus((data >> 16) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus((data >> 8) & 0xFF);
    _dev->endBuffer();
    clock();
    _dev->startBuffer();
    setBus(data & 0xFF);
    clock();
    _dev->endBuffer();
}

void TFTPar8::blockData(uint8_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData8(d[i]);
    }
    streamEnd();
}

void TFTPar8::blockData(uint16_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData16(d[i]);
    }
    streamEnd();
}

void TFTPar8::blockData(uint32_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData32(d[i]);
    }
    streamEnd();
}

