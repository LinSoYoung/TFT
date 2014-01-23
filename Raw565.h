#ifndef _RAW565_H
#define _RAW565_H

#include <TFT.h>

class Raw565 : public Image {
    public:
        Raw565(const uint16_t *data, uint16_t w, uint16_t h);
        void draw(TFT *dev, int16_t x, int16_t y);
        void draw(TFT *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);
    private:
        const uint16_t *_data;
};

#endif
