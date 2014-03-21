/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <TFT.h>

BMP::BMP(const char *data) {
    _data = data;
    _header = (struct BitmapFileHeader *)_data;
    if (_header->bfType != 0x4D42) {
        return;
    }
    _info = (struct BitmapInfoHeader *)(_data + sizeof(struct BitmapFileHeader));
    _image = _data + _header->bfBitmapOffset;
    _width = _info->biWidth;
    _height = _info->biHeight;
}

void BMP::draw(TFT *dev, int16_t x, int16_t y) {
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            if (_info->biBitCount == 32) {
                uint32_t offset = pix * 4;
                struct BitmapPixel32 *p = (struct BitmapPixel32 *)(_image + offset);
                if (p->a == 255) {
                    dev->setPixel(x + ix, y + iy, rgb(p->r, p->g, p->b));
                } else {
                    dev->setPixel(x + ix, y + iy, dev->mix(dev->bgColorAt(x + ix, y + iy), rgb(p->r, p->g, p->b), p->a));
                }
                    
            } else if (_info->biBitCount == 24) {
                uint32_t offset = pix * 3;
                struct BitmapPixel24 *p = (struct BitmapPixel24 *)(_image + offset);
                dev->setPixel(x + ix, y + iy, rgb(p->r, p->g, p->b));
            } else if (_info->biBitCount == 16) {
                uint32_t offset = pix * 2;
                uint16_t *p = (uint16_t *)(_image + offset);
                dev->setPixel(x + ix, y + iy, *p);
            } else {
                dev->setPixel(x + ix, y + iy, rand() & 0xFFFF);
            }
        }
    }
}

void BMP::draw(TFT *dev, int16_t x, int16_t y, uint16_t t) {
    for (uint32_t iy = 0; iy < getHeight(); iy++) {
        uint32_t line = getHeight() - iy - 1;
        for (uint32_t ix = 0; ix < getWidth(); ix++) {
            uint32_t pix = line * getWidth() + ix;
            if (_info->biBitCount == 32) {
                uint32_t offset = pix * 4;
                struct BitmapPixel32 *p = (struct BitmapPixel32 *)(_image + offset);
                if (p->a == 255) {
                    dev->setPixel(x + ix, y + iy, rgb(p->r, p->g, p->b));
                } else {
                    dev->setPixel(x + ix, y + iy, dev->mix(t, rgb(p->r, p->g, p->b), p->a));
                }
            } else if (_info->biBitCount == 24) {
                uint32_t offset = pix * 3;
                struct BitmapPixel24 *p = (struct BitmapPixel24 *)(_image + offset);
                uint16_t c = rgb(p->r, p->g, p->b);
                if (c != t) {
                    dev->setPixel(x + ix, y + iy, rgb(p->r, p->g, p->b));
                }
            } else if (_info->biBitCount == 16) {
                uint32_t offset = pix * 2;
                uint16_t *p = (uint16_t *)(_image + offset);
                uint16_t c = *p;
                if (c != t) {
                    dev->setPixel(x + ix, y + iy, *p);
                }
            } else {
                dev->setPixel(x + ix, y + iy, rand() & 0xFFFF);
            }
        }
    }
}

void BMP::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform) {}
void BMP::drawTransformed(TFT *dev, int16_t x, int16_t y, uint8_t transform, uint16_t t) {}

