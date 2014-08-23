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
 //   translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    buffer->write16(x +(y * _width), color);
}

void Framebuffer565::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < (_width * _height); x++) {
        buffer->write16(x, color);
    }
}

uint16_t Framebuffer565::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = ((s->width * s->height) * s->currentframe);
        uint8_t color = s->data[offset + ((y - s->ypos) * s->width) + (x - s->xpos)];
        return palette[color];
    }

    return buffer->read16((y * _width) + (x));
}

uint16_t Framebuffer565::bgColorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    uint32_t pos = (y * _width) + x;
    return buffer->read16(pos);
}

void Framebuffer565::getScanLine(uint16_t y, uint16_t x, uint16_t w, uint16_t *data) {
	uint16_t bufferdata[w];
	buffer->read16((y * getWidth()) + x, bufferdata, w);
	for (uint16_t px = 0; px < w; px++) {
		struct sprite *s = spriteAt(x + px, y);
		if (s) {
			uint32_t offset = ((s->width * s->height) * s->currentframe);
			uint8_t color = s->data[offset + ((y - s->ypos) * s->width) + (px - s->xpos)];
			data[px] = palette[color];
		} else {
            data[px] = bufferdata[px];
		}
	}
}

void Framebuffer565::update(TFT *tft) {
    update(tft, 0, 0);
}

void Framebuffer565::update(TFT *tft, int16_t x0, int16_t y0) {
    tft->openWindow(x0, y0, _width, _height);
    uint16_t buf[_width];
    for (uint32_t y = 0; y < _height; y++) {
        getScanLine(y, 0, _width, buf);
        tft->windowData(buf, _width);
    }
    tft->closeWindow();
}

