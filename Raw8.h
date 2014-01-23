#ifndef _RAW8_H
#define _RAW8_H

#include <TFT.h>

class Raw8 : public Image {
    public:
        Raw8(const uint8_t *data, uint16_t w, uint16_t h);
        void draw(TFT *dev, int16_t x, int16_t y);
        void draw(TFT *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);
    private:
        const uint8_t *_data;
};

#endif
