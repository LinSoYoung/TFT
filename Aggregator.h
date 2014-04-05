#ifndef _AGGREGATOR_H_
#define _AGGREGATOR_H_

#include <TFT.h>

struct AggregatorList {
    TFT *display;
    int16_t x;
    int16_t y;
    struct AggregatorList *next;
};

class Aggregator : public TFT {
	public:
		Aggregator() : TFT(NULL), _displays(NULL), _width(0), _height(0) {};

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i);
        void displayOn() {}; // Not implemented
        void displayOff() {}; // Not implemented

        void initializeDevice();

        void addDisplay(TFT *d, int16_t x, int16_t y);

        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t c);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t c);

        uint16_t getWidth() { return _width; }
        uint16_t getHeight() { return _height; }

	protected:
        struct AggregatorList *_displays;
        uint16_t _width;
        uint16_t _height;
};

#endif
