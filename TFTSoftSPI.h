#ifndef _TFTSOFTSPI_H
#define _TFTSOFTSPI_H

#include <TFT.h>

/*! The TFTSoftSPI communicator creates an SPI channel on any IO pins.  Not as fast as hardware SPI, but allows extra flexibility. */
class TFTSoftSPI : public TFTCommunicator 
{
    public:
        /*! Create a new software SPI communicator 
         *  ======================================
         *  This constructor takes 4 IO pins and creates a uni-directional (write-only) software SPI channel.
         *  The pins required are Serial Data Out (sdo), Serial Clock (sck), Chip Select (cs) and Data/Command (dc).
         *
         *  Example:
         *
         *      TFTSoftSPI mySPI(4, 5, 6, 7);
         */
        TFTSoftSPI(uint8_t sdo, uint8_t sck, uint8_t cs, uint8_t dc);

        void writeCommand8(uint8_t command);
        void writeCommand16(uint16_t command);
        void writeCommand32(uint32_t command);
        void writeData8(uint8_t data);
        void writeData16(uint16_t data);
        void writeData32(uint32_t data);
        uint8_t readCommand8() { return 0; };
        uint16_t readCommand16() { return 0; };
        uint32_t readCommand32() { return 0; };
        uint8_t readData8() { return 0; };
        uint16_t readData16() { return 0; };
        uint32_t readData32() { return 0; };
        void streamStart();
        void streamEnd();
        void streamCommand8(uint8_t);
        void streamCommand16(uint16_t);
        void streamCommand32(uint32_t);
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);
        uint8_t streamCommand8() { return 0; };
        uint16_t streamCommand16() { return 0; };
        uint32_t streamCommand32() { return 0; };
        uint8_t streamData8() { return 0; };
        uint16_t streamData16() { return 0; };
        uint32_t streamData32() { return 0; };

        void blockData(uint8_t *d, uint32_t c) { };
        void blockData(uint16_t *d, uint32_t c) { };
        void blockData(uint32_t *d, uint32_t c) { };

        void initializeDevice() { };

        uint8_t nativeWidth() { return 8; };

    private:
        uint8_t _sdo;
        uint8_t _sck;
        uint8_t _cs;
        uint8_t _dc;
};

#endif

