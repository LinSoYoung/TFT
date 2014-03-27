/*
 * Copyright (c) , Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 * 
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 * 
 *  3. Neither the name of Majenko Technologies nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef _MCP23S17_H
#define _MCP23S17_H

#define MCP23S17_SPEED 20000000UL

#include <TFT.h>

class MCP23S17 : public ParallelIO {
    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _addr;
    
        uint8_t _reg[22];

        uint8_t _buffer;

        enum {
            IODIRA,     IODIRB,
            IPOLA,      IPOLB,
            GPINTENA,   GPINTENB,
            DEFVALA,    DEFVALB,
            INTCONA,    INTCONB,
            IOCONA,     IOCONB,
            GPPUA,      GPPUB,
            INTFA,      INTFB,
            INTCAPA,    INTCAPB,
            GPIOA,      GPIOB,
            OLATA,      OLATB
        };

        void readRegister(uint8_t addr);
        void writeRegister(uint8_t addr);
        void readAll();
        void writeAll();
    
    public:
        MCP23S17(DSPI *spi, uint8_t cs, uint8_t addr);
        MCP23S17(DSPI &spi, uint8_t cs, uint8_t addr);
        void pinMode(uint16_t pin, uint8_t mode);
        void digitalWrite(uint16_t pin, uint8_t value);
        uint8_t digitalRead(uint16_t pin);
        uint16_t pins() { return 16; }
        void startBuffer();
        void endBuffer();
};
#endif
