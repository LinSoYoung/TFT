#ifndef _TFTPAR16_H
#define _TFTPAR16_H

#include <TFT.h>

/*! The TFTPar16 class creates a full 16-bit parallel interface to a TFT device */
class TFTPar16 : public TFTCommunicator 
{
    public:
        /*! Interface profile for the ITead Studios Arduino Mega TFT Interface Adapter */
        static const uint8_t IteadAdapter[]; 

    public:
        /*! Construct a new 16-bit parallel device using individual pins */
        TFTPar16(uint8_t cs, uint8_t dc, uint8_t clk, 
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, 
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
            uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, 
            uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15) :
                _cs(cs), _dc(dc), _clk(clk),
                _d0(d0), _d1(d1), _d2(d2), _d3(d3),
                _d4(d4), _d5(d5), _d6(d6), _d7(d7),
                _d8(d8), _d9(d9), _d10(d10), _d11(d11),
                _d12(d12), _d13(d13), _d14(d14), _d15(d15) {}

        /*! Construct a new 16-bit parallel device using a pre-programmed profile */
        TFTPar16(const uint8_t *profile) :
            _cs(profile[0]), _dc(profile[1]), _clk(profile[2]),
            _d0(profile[3]), _d1(profile[4]), _d2(profile[5]), _d3(profile[6]),
            _d4(profile[7]), _d5(profile[8]), _d6(profile[9]), _d7(profile[10]),
            _d8(profile[11]), _d9(profile[12]), _d10(profile[13]), _d11(profile[14]),
            _d12(profile[15]), _d13(profile[16]), _d14(profile[17]), _d15(profile[18]) {}

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

        uint8_t nativeWidth() { return 16; }

        void initializeDevice() { }

        void blockData(uint8_t *d, uint32_t);
        void blockData(uint16_t *d, uint32_t);
        void blockData(uint32_t *d, uint32_t);

    private:
        uint8_t _csPolarity;
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
        uint8_t _d8;
        uint8_t _d9;
        uint8_t _d10;
        uint8_t _d11;
        uint8_t _d12;
        uint8_t _d13;
        uint8_t _d14;
        uint8_t _d15;

        void clock();
        void setBus(uint16_t);
};

#endif

