#include <TFT.h>

Framebuffer565Fast::Framebuffer565Fast(int16_t w, int16_t h, uint16_t *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    _buf = b;
}

void Framebuffer565Fast::initializeDevice() {
    fillScreen(0);
}

void Framebuffer565Fast::setPixel(int16_t x, int16_t y, uint16_t color) {
    translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    _buf[x + y * _width] = color;
}

void Framebuffer565Fast::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < _width * _height; x++) {
        _buf[x] = color;
    }
}

uint16_t Framebuffer565Fast::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = s->width * s->height * s->currentframe;
        uint16_t color = palette[s->data[offset + ((y - s->ypos) * s->width) + (x - s->xpos)]];
        return (color);
    }

    return _buf[y * _width + x];
}

uint16_t Framebuffer565Fast::bgColorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    uint32_t pos = y * _width + x;
    return (_buf[pos]);
}

void Framebuffer565Fast::getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data) {
	for (uint16_t px = 0; px < w; px++) {
		struct sprite *s = spriteAt(x + px, y);
		if (s) {
			uint32_t offset = ((s->width * s->height) * s->currentframe);
			uint8_t color = s->data[offset + ((y - s->ypos) * s->width) + (px - s->xpos)];
			data[px] = palette[color];
		} else {
            data[px] = _buf[y * getWidth() + x + px];
		}
	}
}

void Framebuffer565Fast::update(TFT *tft) {
    update(tft, 0, 0);
}

void Framebuffer565Fast::update(TFT *tft, int16_t x0, int16_t y0) {
    tft->openWindow(x0, y0, getWidth(), getHeight());
    uint16_t b[getWidth()];

    for (int y = 0; y < getHeight(); y++) {
        getScanLine(y, 0, getWidth(), b);
        tft->windowData(b, getWidth());
    }
        
    tft->closeWindow();
}

void Framebuffer565Fast::update(TFT &tft) {
    update(tft, 0, 0);
}

void Framebuffer565Fast::update(TFT &tft, int16_t x0, int16_t y0) {
    tft.openWindow(x0, y0, getWidth(), getHeight());
    uint16_t b[getWidth()];

    for (int y = 0; y < getHeight(); y++) {
        getScanLine(y, 0, getWidth(), b);
        tft.windowData(b, getWidth());
    }
    tft.closeWindow();
}


