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
    uint16_t clr = (((uint16_t)c & 0b11) << 3) | (((uint16_t)c & 0b11100) << 6) | (((uint16_t)c & 0b11100000) << 8);
    clr |= ((clr & 0b0010000000000000) ? 0b0001100000000000 : 0);
    clr |= ((clr & 0b0000000100000000) ? 0b0000000011100000 : 0);
    clr |= ((clr & 0b0000000000011000) ? 0b0000000000000111 : 0);
    return clr;
}

void Framebuffer332::setPixel(int16_t x, int16_t y, uint16_t color) {
 //   translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    buffer->write8(x +(y * _width), color565to332(color));
}

void Framebuffer332::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < (_width * _height); x++) {
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
        uint32_t offset = ((s->width * s->height) * s->currentframe);
        uint8_t color = s->data[offset + ((y - s->ypos) * s->width) + (x - s->xpos)];
        return color332to565(color);
    }

    if (!_antiAlias) {
        uint16_t cmm = color332to565(buffer->read8((y * _width) + (x)));
        return cmm;
    }

    uint32_t red=0, green=0, blue=0;

    uint16_t top = 0;
    uint16_t left = 0;
    uint16_t right = 0;
    uint16_t bottom = 0;

    if (y > 0) {
        top = y - 1;
    } else {
        top = y;
    }

    if (y < _height-1) {
        bottom = y + 1;
    } else {
        bottom = y;
    }

    if (x > 0) {
        left = x - 1;
    } else {
        left = x;
    }

    if (x < _width-1) {
        right = x + 1;
    } else {
        right = x;
    }

    uint16_t topline = (top * _width);
    uint16_t midline = (y * _width);
    uint16_t bottomline = (bottom * _width);

    Color565 ctl, ctm, ctr, cml, cmm, cmr, cbl, cbm, cbr;

    ctl.value = color332to565(buffer->read8(topline + left));
    ctm.value = color332to565(buffer->read8(topline + x));
    ctr.value = color332to565(buffer->read8(topline + right));

    cml.value = color332to565(buffer->read8(midline + left));
    cmm.value = color332to565(buffer->read8(midline + x));
    cmr.value = color332to565(buffer->read8(midline + right));

    cbl.value = color332to565(buffer->read8(bottomline + left));
    cbm.value = color332to565(buffer->read8(bottomline + x));
    cbr.value = color332to565(buffer->read8(bottomline + right));

    red += (ctl.r >> 4);
    red += (ctm.r >> 3);
    red += (ctr.r >> 4);
    red += (cml.r >> 3);
    red += (cmm.r >> 1);
    red += (cmr.r >> 3);
    red += (cbl.r >> 4);
    red += (cbm.r >> 3);
    red += (cbr.r >> 4);
    if (red > 0x1F) red = 0x1F;

    green += (ctl.g >> 4);
    green += (ctm.g >> 3);
    green += (ctr.g >> 4);
    green += (cml.g >> 3);
    green += (cmm.g >> 1);
    green += (cmr.g >> 3);
    green += (cbl.g >> 4);
    green += (cbm.g >> 3);
    green += (cbr.g >> 4);
    if (green > 0x3F) green = 0x3F;

    blue += (ctl.b >> 4);
    blue += (ctm.b >> 3);
    blue += (ctr.b >> 4);
    blue += (cml.b >> 3);
    blue += (cmm.b >> 1);
    blue += (cmr.b >> 3);
    blue += (cbl.b >> 4);
    blue += (cbm.b >> 3);
    blue += (cbr.b >> 4);
    if (blue > 0x1F) blue = 0x1F;

    Color565 out;
    out.r = red;
    out.g = green;
    out.b = blue;

    return out.value;
}

uint16_t Framebuffer332::bgColorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    uint32_t pos = (y * _width) + x;
    return color332to565(buffer->read8(pos));
}

void Framebuffer332::getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data) {
	uint8_t bufferdata[w];
	buffer->read8((y * getWidth()) + x, bufferdata, w);
	for (uint16_t px = 0; px < w; px++) {
		struct sprite *s = spriteAt(x + px, y);
		if (s) {
			uint32_t offset = ((s->width * s->height) * s->currentframe);
			uint8_t color = s->data[offset + ((y - s->ypos) * s->width) + (px - s->xpos)];
			data[px] = color332to565(color);
		} else {
            data[px] = color332to565(bufferdata[px]);
		}
	}
}

void Framebuffer332::update(TFT *tft) {
    update(tft, 0, 0);
}

void Framebuffer332::update(TFT *tft, int16_t x0, int16_t y0) {
    tft->openWindow(x0, y0, _width, _height);
    uint16_t buf[_width];
    for (uint32_t y = 0; y < _height; y++) {
        getScanLine(y, 0, _width, buf);
        tft->windowData(buf, _width);
    }
    tft->closeWindow();
}

