#ifndef _IMAGE_H
#define _IMAGE_H

#include <TFT.h>

class Image {
    public:
        static const uint8_t MirrorH = 0x01;
        static const uint8_t MirrorV = 0x02;
        static const uint8_t Rotate180 = 0x03;

        virtual uint16_t getWidth();
        virtual uint16_t getHeight();
        virtual void draw(TFT *dev, int16_t x, int16_t y) = 0;
        virtual void draw(TFT *dev, int16_t x, int16_t y, uint16_t t) = 0;
        virtual void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform) = 0;
        virtual void drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) = 0;

        uint16_t _width;
        uint16_t _height;
};

#endif
