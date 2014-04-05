#ifndef _HX8357_H_
#define _HX8357+H_

#include <TFT.h>

class HX8357 : public TFT 
{
	public:
        static const uint16_t Width      = 320;
        static const uint16_t Height     = 480;

		HX8357(TFTCommunicator *comms) : TFT(comms) {}
		HX8357(TFTCommunicator &comms) : TFT(comms) {}

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

        void openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
        void windowData(uint16_t d);
        void windowData(uint16_t *d, uint32_t l);
        void closeWindow();
		
	protected:
		uint8_t colstart, rowstart;
};

#endif
