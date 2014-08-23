#ifndef _FRAMEBUFFER565FAST_H
#define _FRAMEBUFFER565FAST_H

#include <TFT.h>

class Framebuffer565Fast : public Framebuffer {
    private:
        uint16_t *_buf;

    public:
        Framebuffer565Fast(int16_t w, int16_t h, uint16_t *b);

        // Basic drawing primitives
        void fillScreen(uint16_t c);
        void setPixel(int16_t x, int16_t y, uint16_t c);

        uint16_t colorAt(int16_t x, int16_t y);
        uint16_t bgColorAt(int16_t x, int16_t y);
        void getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data);
        void initializeDevice();

        void update(TFT *tft);
        void update(TFT *tft, int16_t x0, int16_t y0);
        void update(TFT &tft);
        void update(TFT &tft, int16_t x0, int16_t y0);

};

#endif
