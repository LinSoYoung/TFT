#include <TFT.h>

Framebuffer565::Framebuffer565(int16_t w, int16_t h, DataStore *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    buffer = b;
}

void Framebuffer565::initializeDevice() {
    _antiAlias = false;
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

    if (!_antiAlias) {
        return buffer->read16(Math::FastUIntMpy(y, _width) + x);
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

    uint16_t topline = Math::FastUIntMpy(top, _width);
    uint16_t midline = Math::FastUIntMpy(y, _width);
    uint16_t bottomline = Math::FastUIntMpy(bottom, _width);

    Color565 ctl, ctm, ctr, cml, cmm, cmr, cbl, cbm, cbr;

    ctl.value = buffer->read16(topline + left);
    ctm.value = buffer->read16(topline + x);
    ctr.value = buffer->read16(topline + right);

    cml.value = buffer->read16(midline + left);
    cmm.value = buffer->read16(midline + x);
    cmr.value = buffer->read16(midline + right);

    cbl.value = buffer->read16(bottomline + left);
    cbm.value = buffer->read16(bottomline + x);
    cbr.value = buffer->read16(bottomline + right);

    red += (ctl.r >> 4); //Math::Percent(ctl.r,  5);
    red += (ctm.r >> 3); //Math::Percent(ctm.r,  8);
    red += (ctr.r >> 4); //Math::Percent(ctr.r,  5);
    red += (cml.r >> 3); //Math::Percent(cml.r,  8);
    red += (cmm.r >> 1); //Math::Percent(cmm.r, 48);
    red += (cmr.r >> 3); //Math::Percent(cmr.r,  8);
    red += (cbl.r >> 4); //Math::Percent(cbl.r,  5);
    red += (cbm.r >> 3); //Math::Percent(cbm.r,  5);
    red += (cbr.r >> 4); //Math::Percent(cbr.r,  5);
    if (red > 0x1F) red = 0x1F;

    green += (ctl.g >> 4); //Math::Percent(ctl.r,  5);
    green += (ctm.g >> 3); //Math::Percent(ctm.r,  8);
    green += (ctr.g >> 4); //Math::Percent(ctr.r,  5);
    green += (cml.g >> 3); //Math::Percent(cml.r,  8);
    green += (cmm.g >> 1); //Math::Percent(cmm.r, 48);
    green += (cmr.g >> 3); //Math::Percent(cmr.r,  8);
    green += (cbl.g >> 4); //Math::Percent(cbl.r,  5);
    green += (cbm.g >> 3); //Math::Percent(cbm.r,  5);
    green += (cbr.g >> 4); //Math::Percent(cbr.r,  5);
    if (green > 0x3F) green = 0x3F;

    blue += (ctl.b >> 4); //Math::Percent(ctl.r,  5);
    blue += (ctm.b >> 3); //Math::Percent(ctm.r,  8);
    blue += (ctr.b >> 4); //Math::Percent(ctr.r,  5);
    blue += (cml.b >> 3); //Math::Percent(cml.r,  8);
    blue += (cmm.b >> 1); //Math::Percent(cmm.r, 48);
    blue += (cmr.b >> 3); //Math::Percent(cmr.r,  8);
    blue += (cbl.b >> 4); //Math::Percent(cbl.r,  5);
    blue += (cbm.b >> 3); //Math::Percent(cbm.r,  5);
    blue += (cbr.b >> 4); //Math::Percent(cbr.r,  5);
    if (blue > 0x1F) blue = 0x1F;

    Color565 out;
    out.r = red;
    out.g = green;
    out.b = blue;

    return out.value;
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
