#include <TFT.h>

const uint8_t TFTPar16::IteadAdapter[19] = {
0, 1, 2,
3, 4, 5, 6, 7, 8, 9, 10,
11, 12, 13, 14, 15, 16, 17, 18
};


void TFTPar16::clock() {
    digitalWrite(_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk, LOW);
    delayMicroseconds(1);
}

void TFTPar16::setBus(uint16_t value) {
    digitalWrite(_d15, value & 0x8000);
    digitalWrite(_d14, value & 0x4000);
    digitalWrite(_d13, value & 0x2000);
    digitalWrite(_d12, value & 0x1000);
    digitalWrite(_d11, value & 0x0800);
    digitalWrite(_d10, value & 0x0400);
    digitalWrite(_d9, value & 0x0200);
    digitalWrite(_d8, value & 0x0100);
    digitalWrite(_d7, value & 0x0080);
    digitalWrite(_d6, value & 0x0040);
    digitalWrite(_d5, value & 0x0020);
    digitalWrite(_d4, value & 0x0010);
    digitalWrite(_d3, value & 0x0008);
    digitalWrite(_d2, value & 0x0004);
    digitalWrite(_d1, value & 0x0002);
    digitalWrite(_d0, value & 0x0001);
}

void TFTPar16::writeCommand8(uint8_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, _csPolarity);
    setBus(command & 0xFF);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::writeCommand16(uint16_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, _csPolarity);
    setBus(command);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::writeCommand32(uint32_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, _csPolarity);
    setBus((command >> 16) & 0xFFFF);
    clock();
    setBus(command & 0xFFFF);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::streamStart() {
    digitalWrite(_cs, _csPolarity);
}

void TFTPar16::streamEnd() {
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::writeData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, _csPolarity);
    setBus(data);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::writeData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, _csPolarity);
    setBus(data >> 8);
    clock();
    setBus(data & 0xFF);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::writeData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, _csPolarity);
    setBus((data >> 16) & 0xFFFF);
    clock();
    setBus(data & 0xFFFF);
    clock();
    digitalWrite(_cs, !_csPolarity);
}

void TFTPar16::streamCommand8(uint8_t data) {
    digitalWrite(_dc, LOW);
    setBus(data & 0xFF);
    clock();
}

void TFTPar16::streamCommand16(uint16_t data) {
    digitalWrite(_dc, LOW);
    setBus(data);
    clock();
}

void TFTPar16::streamCommand32(uint32_t data) {
    digitalWrite(_dc, LOW);
    setBus((data >> 16) & 0xFFFF);
    clock();
    setBus(data & 0xFFFF);
    clock();
}

void TFTPar16::streamData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    setBus(data & 0xFF);
    clock();
}

void TFTPar16::streamData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    setBus(data);
    clock();
}

void TFTPar16::streamData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 16) & 0xFFFF);
    clock();
    setBus(data & 0xFFFF);
    clock();
}

void TFTPar16::blockData(uint8_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData8(d[i]);
    }
    streamEnd();
}

void TFTPar16::blockData(uint16_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData16(d[i]);
    }
    streamEnd();
}

void TFTPar16::blockData(uint32_t *d, uint32_t c) {
    streamStart();
    for (uint32_t i = 0; i < c; i++) {
        streamData32(d[i]);
    }
    streamEnd();
}

