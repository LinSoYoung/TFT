#ifndef _TFT_H
#define _TFT_H

#if ARDUINO >= 100
# include <Arduino.h>
# include <Print.h>
#else
# include <WProgram.h>
#endif

#define RGB(r,g,b) ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

//#include <algorithm>

#include <stdint.h>

#if defined(__PIC32MX__) || defined(__PIC32MZ__)
#include <DSPI.h>
#endif
#include <SPI.h>

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

extern uint16_t rgb(uint32_t c);
extern uint16_t rgb(uint8_t r, uint8_t g, uint8_t b);

/*! The TFT class describes and controls all the TFT screens.  It acts as a polymorphic parent
 *  class for the other screen drivers, and also contains the generic primative drawing routines.
 *
 *  It is expected that a TFT screen driver will override some functions from this class (some are
 *  pure virtual and must be overridden).
 */
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
        virtual void setCursorX(int16_t x);
        virtual void setCursorY(int16_t y);
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


        void setClipping(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
        void clearClipping();


        /*! \name Pure virtual functions
         *  These are all functions that must be implemented in a TFT driver in order for it to function.
         */
         /**@{*/
    
        /*! Set screen rotation
         *  ===================
         *  This rotates the screen. Value is between 0 and 3, for 0°, 90°, 180° or 270°.
         *
         *  Example:
         *
         *      tft.setRotation(1);
         */
        virtual void setRotation(uint8_t rotation) = 0;
        /*! Draw a pixel
         *  ============
         *  A pixel, coloured (color) is drawn at (x,y).
         *  
         *  Example:
         *  
         *      tft.drawPixel(100, 100, Color::Green);
         */
        virtual void setPixel(int16_t x, int16_t y, uint16_t color) = 0;
        /*! Draw a horizontal line
         *  ======================
         *  A horizontal line of width (w) is drawn from point (x,y) in colour (color);
         * 
         *  Example:
         *
         *      tft.drawHorizontalLine(10, 10, 50, Color::Blue);
         */
        virtual void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) = 0;
        /*! Draw a vertical line
         *  ====================
         *  A vertical line of height (h) is drawn from point (x,y) in colour (color);
         * 
         *  Example:
         *
         *      tft.drawVerticalLine(10, 10, 50, Color::Blue);
         */
        virtual void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) = 0;
        /*! Initialize the display
         *  ======================
         *  The display is configured and made ready to work.  This function *must* be called
         *  before anything can happen on the screen, and it *should* be called before any other function.
         *
         *  Example:
         *
         *      tft.initializeDevice();
         */
        virtual void initializeDevice() = 0;
        /*! Turn on the display
         *  ===================
         *  Enable the video output of the display (if supported).
         *
         *  Example:
         *
         *      tft.displayOn();
         */
        virtual void displayOn() = 0;
        /*! Turn off the display
         *  ====================
         *  Disable the video output of the display (if supported).
         *
         *  Example:
         *
         *      tft.displayOff();
         */
        virtual void displayOff() = 0;
        /*! Invert the display colours
         *  ==========================
         *  All colours become reversed.  Black becomes white, red becomes cyan, etc.
         *
         *  Example:
         *
         *      tft.invertDisplay(true);
         */
        virtual void invertDisplay(boolean i) = 0;
         /**@}*/
        virtual uint16_t stringWidth(const char *text);
        virtual uint16_t stringHeight(const char *text);

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

        /*! The device used to communicate with the TFT screen */
        TFTCommunicator *_comm;
        /*! The text cursor X position */
        int16_t cursor_x;
        /*! The text cursor Y position */
        int16_t cursor_y;
        /*! Whether or not text wrapping is enabled */
        boolean wrap;
        /*! Text foreground colour */
        uint16_t textcolor;
        /*! Text background colour */
        uint16_t textbgcolor;
        /*! Width of the TFT screen */
        uint16_t _width;
        /*! Height of the TFT screen */
        uint16_t _height;
        /*! Current rotation */
        uint8_t rotation;
        uint8_t drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);

        /*! Get screen width
         *  ================
         *  Returns the width (in pixels) of the screen.
         *
         *  Example:
         *
         *    int width = tft.getWidth();
         */
        virtual uint16_t getWidth() { return _width; };
        /*! Get screen height
         *  =================
         *  Returns the height (in pixels) of the screen.
         *
         *  Example:
         *
         *    int height = tft.getHeight();
         */
        virtual uint16_t getHeight() { return _height; };

        point3d rgb2xyz(uint16_t c);
        point3d xyz2lab(point3d c);
        float deltaE(point3d labA, point3d labB);
        uint32_t deltaOrth(uint16_t c1, uint16_t c2);
        static uint32_t rgb2hsv(uint16_t rgb);
        static uint16_t hsv2rgb(uint32_t hsv);

        void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
        void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

        uint16_t mix(uint16_t a, uint16_t b, uint8_t pct);

        boolean clipToScreen(int16_t &x, int16_t &y, int16_t &w, int16_t &h);

        void fatalError(const char *title, const char *message);

        void setFontScaleX(uint8_t sx);
        void setFontScaleY(uint8_t sy);

        int16_t _clip_x0;
        int16_t _clip_x1;
        int16_t _clip_y0;
        int16_t _clip_y1;

    protected:
        /*! A pointer to the currently selected font table */
        const uint8_t *font;
        /*! The current X scaling factor of the font */
        uint8_t font_scale_x;
        /*! The current Y scaling factor of the font */
        uint8_t font_scale_y;

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
#include "TFTPar16.h"
#include "RawPar.h"
#include "TFTPMP.h"
#include "CoreIO.h"

// Storage devices
#include "SPISRAM.h"
#include "SRAM.h"
#include "Rambo.h"

// Virtual display devices
#include "Framebuffer.h"
#include "Framebuffer1.h"
#include "Framebuffer332.h"
#include "Framebuffer332Fast.h"
#include "Framebuffer565.h"
#include "Framebuffer565Fast.h"
#include "Aggregator.h"

// Supported devices
#include "ST7735.h"
#include "KS0108.h"
#include "LEDMatrix.h"
#include "HD44780.h"
#include "ILI9340.h"
#include "BD663474.h"
#include "SSD1289.h"
#include "SSD1963.h"
#include "HX8357.h"
#include "PICadillo35t.h"
#include "S6D0164.h"

// Touchscreen devices
#include "Touch.h"
#include "XPT2046.h"
#include "AnalogTouch.h"

// Colour filtering system
#include "Filter.h"

// Image formats
#include "RLE.h"
#include "Raw565.h"
#include "Raw8.h"
#include "BMP.h"

#endif


