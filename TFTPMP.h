#ifndef _TFTPMP_H
#define _TFTPMP_H

#include <TFT.h>

class TFTPMP : public TFTCommunicator 
{
    private:
        static const uint8_t opWrite = 0;
        static const uint8_t opRead = 1;
        uint8_t _lastOp;

    public:
        TFTPMP();
        uint8_t inline readCommand8();
        uint16_t inline readCommand16();
        uint32_t inline readCommand32();
        uint8_t inline readData8();
        uint16_t inline readData16();
        uint32_t inline readData32();
        void inline writeCommand8(uint8_t command);
        void inline writeCommand16(uint16_t command);
        void inline writeCommand32(uint32_t command);
        void inline writeData8(uint8_t data);
        void inline writeData16(uint16_t data);
        void inline writeData32(uint32_t data);
        void inline streamStart();
        void inline streamEnd();
        uint8_t inline streamCommand8();
        uint16_t  inline streamCommand16();
        uint32_t inline streamCommand32();
        uint8_t inline streamData8();
        uint16_t inline streamData16();
        uint32_t inline streamData32();
        void inline streamCommand8(uint8_t);
        void inline streamCommand16(uint16_t);
        void inline streamCommand32(uint32_t);
        void inline streamData8(uint8_t);
        void inline streamData16(uint16_t);
        void inline streamData32(uint32_t);
        void inline blockData(uint8_t *, uint32_t);
        void inline blockData(uint16_t *, uint32_t);
        void inline blockData(uint32_t *, uint32_t);

        uint8_t inline nativeWidth() { return 16; };
        void initializeDevice();
};

#endif

