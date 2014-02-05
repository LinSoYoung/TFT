#include <TFT.h>

Framebuffer565::Framebuffer565(int16_t w, int16_t h, DataStore *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    buffer = b;
}

void Framebuffer565::initializeDevice() {
    buffer->initializeDevice();
}

void Framebuffer565::setPixel(int16_t x, int16_t y, uint16_t color) {
    translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    buffer->write16(x + Math::FastUIntMpy(y, _width), color);
}

void Framebuffer565::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < Math::FastUIntMpy(_width, _height); x++) {
        buffer->write16(x, color);
    }
}

void Framebuffer565::setColor(uint8_t color, uint16_t rgb) {
}

void Framebuffer565::setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
}

void Framebuffer565::loadPalette(const uint16_t *p) {
}

void Framebuffer565::loadPalette(const uint8_t p[256][3]) {
}

void Framebuffer565::loadPalette(Framebuffer *fb) {
}

uint16_t Framebuffer565::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = Math::FastUIntMpy(Math::FastUIntMpy(s->width, s->height), s->currentframe);
        uint16_t color = s->data[offset + Math::FastUIntMpy((y - s->ypos), s->width) + (x - s->xpos)];
        return (color);
    }
    uint16_t cmm = (buffer->read16(Math::FastUIntMpy(y, _width) + (x)));
    return cmm;
}

uint16_t Framebuffer565::bgColorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    uint32_t pos = Math::FastUIntMpy(y, _width) + x;
    return (buffer->read16(pos));
}

void Framebuffer565::getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data) {
	uint16_t bufferdata[w];
	buffer->read16(Math::FastUIntMpy(y, getWidth()) + x, bufferdata, w);
	for (uint16_t px = 0; px < w; px++) {
		struct sprite *s = spriteAt(x + px, y);
		if (s) {
			uint32_t offset = Math::FastUIntMpy(Math::FastUIntMpy(s->width, s->height), s->currentframe);
			uint8_t color = s->data[offset + Math::FastUIntMpy((y - s->ypos), s->width) + (px - s->xpos)];
			data[px] = color;
		} else {
            data[px] = bufferdata[px];
		}
	}
}
