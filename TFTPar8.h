#ifndef _TFTPAR8_H
#define _TFTPAR8_H

#include <TFT.h>

class TFTPar8 : public TFTCommunicator 
{
    public:
        TFTPar8(ParallelIO *dev, uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
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
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);

        uint8_t streamCommand8() { return 0; }
        uint16_t streamCommand16() { return 0; }
        uint32_t streamCommand32() { return 0; }

        uint8_t streamData8() { return 0; }
        uint16_t streamData16() { return 0; }
        uint32_t streamData32() { return 0; }

        uint8_t readCommand8() { return 0; }
        uint16_t readCommand16() { return 0; }
        uint32_t readCommand32() { return 0; }
        uint8_t readData8() { return 0; }
        uint16_t readData16() { return 0; }
        uint32_t readData32() { return 0; }

        uint8_t nativeWidth() { return 8; }

        void initializeDevice() { }

        void blockData(uint8_t *d, uint32_t);
        void blockData(uint16_t *d, uint32_t);
        void blockData(uint32_t *d, uint32_t);

    private:
        ParallelIO *_dev;
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _clk;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _d4;
        uint8_t _d5;
        uint8_t _d6;
        uint8_t _d7;

        void clock();
        void setBus(uint8_t);
};

#endif

