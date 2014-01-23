#ifndef _RLE_H
#define _RLE_H

#include <TFT.h>

class RLE : public Image {
    public:
        RLE(const uint8_t *data);
        void draw(TFT *dev, int16_t x, int16_t y);
        void draw(TFT *dev, int16_t x, int16_t y, uint16_t t);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform);
        void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t);
    private:
        const uint8_t *_data;
        uint8_t _depth;
        uint32_t _size;
};

#endif
