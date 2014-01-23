#include <TFT.h>

Raw565::Raw565(const uint16_t *data, uint16_t w, uint16_t h) {
    _data = data;
    _width = w;
    _height = h;
}

void Raw565::draw(TFT *dev, int16_t x, int16_t y) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            dev->setPixel(x + px, y + py, _data[p++]);
        }
    }
}

void Raw565::draw(TFT *dev, int16_t x, int16_t y, uint16_t t) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            if (_data[p] != t) {
                dev->setPixel(x + px, y + py, _data[p]);
            }
            p++;
        }
    }
}

void Raw565::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            switch (transform) {
                default:
                    dev->setPixel(x + px, y + py, _data[p]);
                    break;
                case MirrorH:
                    dev->setPixel(getWidth() - (x + px) - 1, y + py, _data[p]);
                    break;
                case MirrorV:
                    dev->setPixel(x + px, getHeight() - (y + py) - 1, _data[p]);
                    break;
                case Rotate180:
                    dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _data[p]);
                    break;
            }
            p++;
        }
    }
}

void Raw565::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) {
    uint32_t p = 0;
    for (int py = 0; py < getHeight(); py++) {
        for (int px = 0; px < getWidth(); px++) {
            if (_data[p] != t) {
                switch (transform) {
                    default:
                        dev->setPixel(x + px, y + py, _data[p]);
                        break;
                    case MirrorH:
                        dev->setPixel(getWidth() - (x + px) - 1, y + py, _data[p]);
                        break;
                    case MirrorV:
                        dev->setPixel(x + px, getHeight() - (y + py) - 1, _data[p]);
                        break;
                    case Rotate180:
                        dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _data[p]);
                        break;
                }
            }
            p++;
        }
    }
}
