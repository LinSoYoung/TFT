#ifndef _SPISRAM_H
#define _SPISRAM_H

#include <TFT.h>

class SPISRAM : public DataStore {
    public:
#if defined(__PIC32MX__) || defined(__PIC32MZ__)
        SPISRAM(DSPI *spi, uint8_t cs, uint32_t s) : _dspi(spi), _spi(NULL), _cs(cs), _size(s) {}
        SPISRAM(DSPI &spi, uint8_t cs, uint32_t s) : _dspi(&spi), _spi(NULL), _cs(cs), _size(s) {}
#endif
        SPISRAM(SPIClass *spi, uint8_t cs, uint32_t s) : _spi(spi), _cs(cs), _size(s) {}
        SPISRAM(SPIClass &spi, uint8_t cs, uint32_t s) : _spi(&spi), _cs(cs), _size(s) {}
        uint8_t read8(uint32_t address);
        uint16_t read16(uint32_t address);
        uint32_t read32(uint32_t address);

        void read8(uint32_t address, uint8_t *data, uint32_t len);
        void read16(uint32_t address, uint16_t *data, uint32_t len);
        void read32(uint32_t address, uint32_t *data, uint32_t len);

        void write8(uint32_t address, uint8_t data);
        void write16(uint32_t address, uint16_t data);
        void write32(uint32_t address, uint32_t data);

        void write8(uint32_t address, uint8_t *data, uint32_t len);
        void write16(uint32_t address, uint16_t *data, uint32_t len);
        void write32(uint32_t address, uint32_t *data, uint32_t len);

        void setAll8(uint8_t data);
        void setAll16(uint16_t data);
        void setAll32(uint32_t data);

        void initializeDevice();
        uint32_t size() { return _size; }
    private:
        uint8_t xfer(uint8_t);
        void setSpeed();
        uint32_t _size;
        uint8_t _cs;
#if defined(__PIC32MX__) || defined(__PIC32MZ__)
        DSPI *_dspi;
#endif
        SPIClass *_spi;
};

#endif
