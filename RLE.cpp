#include <TFT.h>

RLE::RLE(const uint8_t *data) {
    _data = data;
    _width = 0;
    _height = 0;
    _depth = 0;
    if (_data[0] == 'R' && _data[1] == 'L' && _data[2] == 'E') {
        _depth = _data[3];
        _size = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
        _width = data[8] << 8 | data[9];
        _height = data[10] << 8 | data[11];
    }
}

void RLE::draw(TFT *dev, int16_t x, int16_t y) {
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < _size) {
        if (_data[12+i] != _data[13+i]) {
            uint16_t col = _data[12+i];
            if (_filter != NULL) {
                col = _filter->process(col);
            }
            dev->setPixel(x + px, y + py, col);
            i++;
            px ++;
            if (px == getWidth()) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = _data[12+i];
            if (_depth == 8) {
                len = _data[14+i];
                i += 3;
            } else if (_depth == 16) {
                len = _data[14+i] << 8 | _data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                if (_filter != NULL) {
                    col = _filter->process(col);
                }
                dev->setPixel(x + px, y + py, col);
                px ++;
                if (px == getWidth()) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

void RLE::draw(TFT *dev, int16_t x, int16_t y, uint16_t t) {
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < _size) {
        if (_data[12+i] != _data[13+i]) {
            if (_data[12+i] != t) {
                uint16_t col = _data[12+i];
                if (_filter != NULL) {
                    col = _filter->process(col);
                }
                dev->setPixel(x + px, y + py, col);
            }
            i++;
            px ++;
            if (px == getWidth()) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = _data[12+i];
            if (_depth == 8) {
                len = _data[14+i];
                i += 3;
            } else if (_depth == 16) {
                len = _data[14+i] << 8 | _data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                if (col != t) {
                    if (_filter != NULL) {
                        col = _filter->process(col);
                    }
                    dev->setPixel(x + px, y + py, col);
                }
                px ++;
                if (px == getWidth()) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

void RLE::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform) {
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < _size) {
        if (_data[12+i] != _data[13+i]) {
            switch (transform) {
                default:
                    dev->setPixel(x + px, y + py, _data[12+i]);
                    break;
                case MirrorH:
                    dev->setPixel(getWidth() - (x + px) - 1, y + py, _data[12+i]);
                    break;
                case MirrorV:
                    dev->setPixel(x + px, getHeight() - (y + py) - 1, _data[12+i]);
                    break;
                case Rotate180:
                    dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, _data[12+i]);
                    break;
            }
            i++;
            px ++;
            if (px == getWidth()) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = _data[12+i];
            if (_depth == 8) {
                len = _data[14+i];
                i += 3;
            } else if (_depth == 16) {
                len = _data[14+i] << 8 | _data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                switch (transform) {
                    default:
                        dev->setPixel(x + px, y + py, col);
                        break;
                    case MirrorH:
                        dev->setPixel(getWidth() - (x + px) - 1, y + py, col);
                        break;
                    case MirrorV:
                        dev->setPixel(x + px, getHeight() - (y + py) - 1, col);
                        break;
                    case Rotate180:
                        dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, col);
                        break;
                }
                px ++;
                if (px == getWidth()) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

void RLE::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) {
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < _size) {
        if (_data[12+i] != _data[13+i]) {
            uint16_t col = _data[12+i];
            if (_filter != NULL) {
                col = _filter->process(col);
            }
            if (_data[12+i] != t) {
                switch (transform) {
                    default:
                        dev->setPixel(x + px, y + py, col);
                        break;
                    case MirrorH:
                        dev->setPixel(getWidth() - (x + px) - 1, y + py, col);
                        break;
                    case MirrorV:
                        dev->setPixel(x + px, getHeight() - (y + py) - 1, col);
                        break;
                    case Rotate180:
                        dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, col);
                        break;
                }
            }
            i++;
            px ++;
            if (px == getWidth()) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = _data[12+i];
            if (_depth == 8) {
                len = _data[14+i];
                i += 3;
            } else if (_depth == 16) {
                len = _data[14+i] << 8 | _data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                if (col != t) {
                    if (_filter != NULL) {
                        col = _filter->process(col);
                    }
                    switch (transform) {
                        default:
                            dev->setPixel(x + px, y + py, col);
                            break;
                        case MirrorH:
                            dev->setPixel(getWidth() - (x + px) - 1, y + py, col);
                            break;
                        case MirrorV:
                            dev->setPixel(x + px, getHeight() - (y + py) - 1, col);
                            break;
                        case Rotate180:
                            dev->setPixel(getWidth() - (x + px) - 1, getHeight() - (y + py) - 1, col);
                            break;
                    }
                }
                px ++;
                if (px == getWidth()) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}
