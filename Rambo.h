#ifndef _RAMBO_H
#define _RAMBO_H

#include <TFT.h>

#define MAXCHIPS 16 

class Rambo : public DataStore {
    public:
        Rambo(DSPI *spi, uint32_t s, uint8_t cs0, uint8_t cs1 = NOT_A_PIN, uint8_t cs2 = NOT_A_PIN, uint8_t cs3 = NOT_A_PIN, uint8_t cs4 = NOT_A_PIN, uint8_t cs5 = NOT_A_PIN, uint8_t cs6 = NOT_A_PIN, uint8_t cs7 = NOT_A_PIN, uint8_t cs8 = NOT_A_PIN, uint8_t cs9 = NOT_A_PIN, uint8_t cs10 = NOT_A_PIN, uint8_t cs11 = NOT_A_PIN, uint8_t cs12 = NOT_A_PIN, uint8_t cs13 = NOT_A_PIN, uint8_t cs14 = NOT_A_PIN, uint8_t cs15 = NOT_A_PIN);

        uint8_t read8(uint32_t address);
        void read8(uint32_t address, uint8_t *data, uint32_t len);
        void write8(uint32_t address, uint8_t data);
        void write8(uint32_t address, uint8_t *data, uint32_t len);

        uint16_t read16(uint32_t address);
        void read16(uint32_t address, uint16_t *data, uint32_t len);
        void write16(uint32_t address, uint16_t data);
        void write16(uint32_t address, uint16_t *data, uint32_t len);

        uint32_t read32(uint32_t address);
        void read32(uint32_t address, uint32_t *data, uint32_t len);
        void write32(uint32_t address, uint32_t data);
        void write32(uint32_t address, uint32_t *data, uint32_t len);

        void initializeDevice();
        uint8_t operator[](uint32_t address) { return read8(address); }
        uint32_t size() { return _size; }

        void setAll8(uint8_t);
        void setAll16(uint16_t);
        void setAll32(uint32_t);

        uint8_t chips() { return _chips; }

    private:
        uint32_t _size;
        uint32_t _chipsize;
        uint8_t _chips;
        uint8_t _cs[MAXCHIPS];
        DSPI *_spi;
};

#endif
