#ifndef _TFT_H
#define _TFT_H

#if ARDUINO >= 100
# include <Arduino.h>
# include <Print.h>
#else
# include <WProgram.h>
#endif

#define RGB(r,g,b) ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

#include <algorithm>

#include <stdint.h>
#include <DSPI.h>

// Base classes
#include "TFTCommunicator.h"
#include "DataStore.h"
#include "Color.h"
#include "Fonts.h"
#include "ParallelIO.h"

// Utility Classes
#include "MathFuncs.h"

typedef struct {
    uint8_t linesPerCharacter;
    uint8_t bytesPerLine;
    uint8_t startGlyph;
    uint8_t endGlyph;
    uint8_t bitsPerPixel;
} FontHeader;

struct coord {
    uint16_t x;
    uint16_t y;
};

typedef struct {
    float x;
    float y;
    float z;
} point3d;

typedef struct {
    union {
        uint16_t value;
        struct {
            unsigned r:5;
            unsigned g:6;
            unsigned b:5;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed)) Color565;

class Framebuffer;

extern uint16_t rgb(uint32_t c);
extern uint16_t rgb(uint8_t r, uint8_t g, uint8_t b);

class TFT : public Print
{
    public:
        TFT();
        TFT(TFTCommunicator *comms);
        TFT(TFTCommunicator &comms);
        virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        virtual void drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        virtual void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        virtual void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        virtual void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
        virtual void drawRGB(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h);
        virtual void drawRGBA(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, uint16_t trans);
        virtual void setCursor(int16_t x, int16_t y);
        virtual int16_t getCursorX();
        virtual int16_t getCursorY();
        virtual int16_t getCursor(boolean x);
        virtual void setTextColor(uint16_t c);
        virtual void setTextColor(uint16_t fg, uint16_t bg);
        virtual uint16_t getTextColor();
        virtual void invertTextColor();
        virtual void setTextWrap(boolean w);
        virtual uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
        virtual void setFont(const uint8_t *f);

        virtual void fillScreen(uint16_t color);
        virtual void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        virtual void setPixel(int16_t x, int16_t y, uint16_t color) = 0;
        virtual void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) = 0;
        virtual void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) = 0;
        virtual void initializeDevice() = 0;
        virtual void displayOn() = 0;
        virtual void displayOff() = 0;
        virtual void invertDisplay(boolean i) = 0;
        virtual void update(Framebuffer *fb);
        virtual void update(Framebuffer *fb, int16_t dx, int16_t dy);
        virtual uint16_t stringWidth(char *text);
        virtual uint16_t stringHeight(char *text);

        virtual void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        virtual void windowData(uint16_t d);
        virtual void windowData(uint16_t *d, uint32_t l);
        virtual void closeWindow();

        virtual uint16_t bgColorAt(int16_t x, int16_t y);
        virtual uint16_t colorAt(int16_t x, int16_t y);
#if ARDUINO >= 100
        size_t write(uint8_t c);
#else
        void write(uint8_t c);
#endif
        TFTCommunicator *_comm;
        int16_t cursor_x, cursor_y;
        uint8_t textsize;
        boolean wrap;
        uint16_t textcolor, textbgcolor;
        uint16_t _width;
        uint16_t _height;
        uint8_t rotation;
        uint8_t drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);

        virtual uint16_t getWidth() { return _width; };
        virtual uint16_t getHeight() { return _height; };

        point3d rgb2xyz(uint16_t c);
        point3d xyz2lab(point3d c);
        float deltaE(point3d labA, point3d labB);
        uint32_t deltaOrth(uint16_t c1, uint16_t c2);
        uint32_t rgb2hsv(uint16_t rgb);

        void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
        void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

        uint16_t mix(uint16_t a, uint16_t b, uint8_t pct);

        boolean clipToScreen(int16_t &x, int16_t &y, int16_t &w, int16_t &h);

    protected:
        const uint8_t *font;

    private:
        uint16_t winx0;
        uint16_t winy0;
        uint16_t winx1;
        uint16_t winy1;
        uint16_t winpx;
        uint16_t winpy;

};

#include "Image.h"

#include "TFTDSPI.h"

#include "TFTSoftSPI.h"
#include "TFTPar4.h"
#include "TFTPar8.h"
#include "RawPar.h"
#include "TFTPMP.h"
#include "MCP23S17.h"
#include "CoreIO.h"

// Storage devices
#include "SPISRAM.h"
#include "SRAM.h"

// Virtual display devices
#include "Framebuffer.h"
#include "Framebuffer1.h"
#include "Framebuffer332.h"
#include "Framebuffer332Fast.h"
#include "Framebuffer565.h"
#include "Aggregator.h"

// Supported devices
#include "ST7735.h"
#include "KS0108.h"
#include "LEDMatrix.h"
#include "HD44780.h"
#include "DOGMe.h"
#include "ILI9340.h"
#include "BD663474.h"
#include "SSD1289.h"
#include "SSD1963.h"
#include "HX8357.h"

// Touchscreen devices
#include "Touch.h"
#include "XPT2046.h"
#include "AnalogTouch.h"

// Image formats
#include "RLE.h"
#include "Raw565.h"
#include "Raw8.h"
#include "BMP.h"

#endif


