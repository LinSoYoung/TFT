#include <TFT.h>

#define GLCD_CMD_OFF         0b00111110
#define GLCD_CMD_ON          0b00111111
#define GLCD_CMD_SET_Y       0b01000000
#define GLCD_CMD_SET_PAGE    0b10111000
#define GLCD_CMD_START       0b11000000

#define GLCD_STAT_BUSY   0b10000000
#define GLCD_STAT_ONOFF  0b00100000
#define GLCD_STAT_RESET  0b00010000

#define C2B(X, Y) (((Y) << 6) + (X))

void KS0108::initializeDevice() {
    _width  = 64;
    _height = 64;
    _comm->initializeDevice();
    _comm->writeCommand8(GLCD_CMD_ON);
    _comm->writeCommand8(GLCD_CMD_START);
}

void KS0108::setPage(uint8_t page)
{
    _comm->writeCommand8(GLCD_CMD_SET_PAGE | (page & 0x07));
}

void KS0108::setY(uint8_t y)
{
    _comm->writeCommand8(GLCD_CMD_SET_Y | (y & 63));
}

void KS0108::setPixel(int16_t x, int16_t y, uint16_t color) {
    doSetPixel(x, y, color);
    y = y >> 3;
    setPage(y);
    setY(x);
    _comm->writeData8(this->buffer[C2B(x, y)]);
}

void KS0108::doSetPixel(int16_t x, int16_t y, uint16_t color) {
    uint8_t row;
    uint8_t pixel;
    uint8_t mask;

	if((x < 0) ||(x >= 64) || (y < 0) || (y >= 64)) 
		return;

    row = y>>3;
    pixel = y & 0x07;
    mask = 1<<pixel;
    if (color) {
        this->buffer[C2B(x, row)] |= mask;
    } else {
        this->buffer[C2B(x, row)] &= ~mask;
    }
}

void KS0108::fillScreen(uint16_t color) {
    for (int16_t y = 0; y < _height/8; y++) {
        for (int16_t x = 0; x < _width; x++) {
            this->buffer[C2B(x, y)] = color ? 0xFF : 0x00;
        }
    }
    updateScreen();
}

void KS0108::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;

    for (int16_t dy = y; dy < y + h; dy++) {
        for (int16_t dx = x; dx < x + w; dx++) {
            setPixel(dx, dy, color);
        }
    }
    updateScreen();
}

void KS0108::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    drawLine(x, y, x + w, y, color);
    updateScreen();
}

void KS0108::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    drawLine(x, y, x, y + h, color);
    updateScreen();
}

void KS0108::invertDisplay(boolean i) {
    for (int16_t y = 0; y < _height/8; y++) {
        for (int16_t x = 0; x < _width; x++) {
            this->buffer[C2B(x, y)] = ~this->buffer[C2B(x, y)];
        }
    }
    updateScreen();
}

void KS0108::updateScreen() {
    uint8_t x,y;
    for(y=0; y<8; y++)
    {
        this->setPage(y);
        this->setY(0);
        for(x=0; x<64; x++)
        {
            _comm->writeData8(this->buffer[C2B(x, y)]);
        }
    }
}
