#ifndef _S6D0164_H_
#define _S6D0164_H_

#include <TFT.h>

class S6D0164 : public TFT 
{

    private:
        void LCD_Write_COM(uint8_t c);
        void LCD_Write_COM_DATA(uint8_t c, uint16_t d);
        void LCD_Write_DATA(uint16_t d);

	public:
        static const uint16_t Width      = 176;
        static const uint16_t Height     = 220;

		S6D0164(TFTCommunicator *comms) : TFT(comms) {}
		S6D0164(TFTCommunicator &comms) : TFT(comms) {}

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
};

#endif
