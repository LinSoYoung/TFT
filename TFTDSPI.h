#ifndef _TFTDSPI_H
#define _TFTDSPI_H

#include <TFT.h>

/*! The TFTDSPI class creates a new SPI interface using the chipKIT DSPI library. */
class TFTDSPI : public TFTCommunicator 
{
    public:
        /**@{*/
        /*! Construct a new SPI communication object.  Pass either a pointer or reference to a DSPI object, a Chip Select pin, a Data/Command pin and (optionally) a communication speed.
         *
         *  Example:
         *
         *      DSPI0 spi;
         *      TFTDSPI mySPI(spi, 10, 8);
         */
        TFTDSPI(DSPI *spi, uint8_t cs, uint8_t dc = 255, uint32_t sp=40000000UL) : _spi(spi), _cs(cs), _dc(dc), _speed(sp) {}
        TFTDSPI(DSPI &spi, uint8_t cs, uint8_t dc = 255, uint32_t sp=40000000UL) : _spi(&spi), _cs(cs), _dc(dc), _speed(sp) {}
        /**@}*/

        void initializeDevice();
        uint8_t readCommand8();
        uint16_t readCommand16();
        uint32_t readCommand32();
        uint8_t readData8();
        uint16_t readData16();
        uint32_t readData32();
        void writeCommand8(uint8_t command);
        void writeCommand16(uint16_t command);
        void writeCommand32(uint32_t command);
        void writeData8(uint8_t data);
        void writeData16(uint16_t data);
        void writeData32(uint32_t data);
        void streamStart();
        void streamEnd();
        void streamCommand8(uint8_t);
        void streamCommand16(uint16_t);
        void streamCommand32(uint32_t);
        uint8_t streamCommand8();
        uint16_t streamCommand16();
        uint32_t streamCommand32();
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);
        uint8_t streamData8();
        uint16_t streamData16();
        uint32_t streamData32();
        uint8_t nativeWidth() { return 32; };
        void blockData(uint8_t *data, uint32_t len);
        void blockData(uint16_t *data, uint32_t len);
        void blockData(uint32_t *data, uint32_t len);

    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
        uint32_t _speed;
};

#endif

