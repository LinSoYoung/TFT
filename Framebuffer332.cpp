#include <TFT.h>

Framebuffer332::Framebuffer332(int16_t w, int16_t h, DataStore *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    buffer = b;
}

void Framebuffer332::initializeDevice() {
    buffer->initializeDevice();
}

static inline uint8_t color565to332(uint16_t c) {
    uint16_t t = ((c & 0b11000) >> 3) | ((c & 0b11100000000) >> 6) | ((c & 0b1110000000000000) >> 8);
    return t & 0xFF;
}

static inline uint16_t color332to565(uint8_t c) {
    return (((uint16_t)c & 0b11) << 3) | (((uint16_t)c & 0b11100) << 6) | (((uint16_t)c & 0b11100000) << 8);
}

void Framebuffer332::setPixel(int16_t x, int16_t y, uint16_t color) {
    translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    buffer->write8(x + Math::FastUIntMpy(y, _width), color565to332(color));
}

void Framebuffer332::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < Math::FastUIntMpy(_width, _height); x++) {
        buffer->write8(x, color565to332(color));
    }
}

void Framebuffer332::setColor(uint8_t color, uint16_t rgb) {
}

void Framebuffer332::setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
}

void Framebuffer332::loadPalette(const uint16_t *p) {
}

void Framebuffer332::loadPalette(const uint8_t p[256][3]) {
}

void Framebuffer332::loadPalette(Framebuffer *fb) {
}

uint16_t Framebuffer332::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = Math::FastUIntMpy(Math::FastUIntMpy(s->width, s->height), s->currentframe);
        uint8_t color = s->data[offset + Math::FastUIntMpy((y - s->ypos), s->width) + (x - s->xpos)];
        return color332to565(color);
    }
    uint32_t pos = Math::FastUIntMpy(y, _width) + x;
    return color332to565(buffer->read8(pos));
}

uint16_t Framebuffer332::bgColorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    uint32_t pos = Math::FastUIntMpy(y, _width) + x;
    return color332to565(buffer->read8(pos));
}

void Framebuffer332::getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data) {
	uint8_t bufferdata[w];
	buffer->read8(Math::FastUIntMpy(y, getWidth()) + x, bufferdata, w);
	for (uint16_t px = 0; px < w; px++) {
		struct sprite *s = spriteAt(x + px, y);
		if (s) {
			uint32_t offset = Math::FastUIntMpy(Math::FastUIntMpy(s->width, s->height), s->currentframe);
			uint8_t color = s->data[offset + Math::FastUIntMpy((y - s->ypos), s->width) + (px - s->xpos)];
			data[px] = color332to565(color);
		} else {
            data[px] = color332to565(bufferdata[px]);
		}
	}
}
