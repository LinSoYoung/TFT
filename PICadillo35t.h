#ifndef _PICADILLO35T_H_
#define _PICADILLO35T_H_

#include <TFT.h>

class PICadillo35t : public TFT 
{
	public:
        static const uint16_t Width      = 320;
        static const uint16_t Height     = 480;

		PICadillo35t() : TFT(NULL) {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn();  
        void displayOff();  

        void initializeDevice();

        //void update(Framebuffer *fb); // Not implemented

        void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void windowData(uint16_t d);
        void windowData(uint16_t *d, uint32_t l);
        void closeWindow();

        void inline __attribute__((alwaysinline)) writeCommand(uint16_t);
        void inline __attribute__((alwaysinline)) writeData(uint16_t);
		
	protected:
		uint8_t colstart, rowstart;
};

#endif
