#ifndef _FRAMEBUFFER565_H
#define _FRAMEBUFFER565_H

#include <TFT.h>

class Framebuffer565 : public Framebuffer {
    public:
        Framebuffer565(int16_t w, int16_t h, DataStore *b);

        // Basic drawing primitives
        void fillScreen(uint16_t c);
        void setPixel(int16_t x, int16_t y, uint16_t c);

        uint16_t colorAt(int16_t x, int16_t y);
        uint16_t bgColorAt(int16_t x, int16_t y);
        void getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data);
        void initializeDevice();
        void update(TFT *);
        void update(TFT *, int16_t x0, int16_t y0);
};

#endif
