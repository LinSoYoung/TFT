#include <TFT.h>
#if defined(__PIC32MX__) || defined(__PIC32MZ__)

#define S6D0164_SYSTEM                  0x00
#define S6D0164_OUTPUT                  0x01
#define S6D0164_WAVEFORM                0x02
#define S6D0164_ENTRY_MODE              0x03
#define S6D0164_DISPLAY                 0x07
#define S6D0164_BLANK_PERIOD            0x08
#define S6D0164_FRAME_CYCLE             0x0B
#define S6D0164_INTERFACE               0x0C
#define S6D0164_OSCILLATOR              0x0F
#define S6D0164_POWER_1                 0x10
#define S6D0164_POWER_2                 0x11
#define S6D0164_POWER_3                 0x12
#define S6D0164_POWER_4                 0x13
#define S6D0164_POWER_5                 0x14
#define S6D0164_VCI                     0x15
#define S6D0164_GRAM_ADDRESS_SET_X      0x20
#define S6D0164_GRAM_ADDRESS_SET_Y      0x21
#define S6D0164_GRAM_RW                 0x22
#define S6D0164_SOFT_RESET              0x28
#define S6D0164_VERTICAL_SCROLL_1A      0x31
#define S6D0164_VERTICAL_SCROLL_1B      0x32
#define S6D0164_VERTICAL_SCROLL_2       0x33
#define S6D0164_PARTIAL_1               0x34
#define S6D0164_PARTIAL_2               0x35
#define S6D0164_HORIZ_END               0x36
#define S6D0164_HORIZ_START             0x37
#define S6D0164_VERT_END                0x38
#define S6D0164_VERT_START              0x39
#define S6D0164_GAMMA_0                 0x50
#define S6D0164_GAMMA_1                 0x51
#define S6D0164_GAMMA_2                 0x52
#define S6D0164_GAMMA_3                 0x53
#define S6D0164_GAMMA_4                 0x54
#define S6D0164_GAMMA_5                 0x55
#define S6D0164_GAMMA_6                 0x56
#define S6D0164_GAMMA_7                 0x57
#define S6D0164_GAMMA_8                 0x58
#define S6D0164_GAMMA_9                 0x59
#define S6D0164_TEST_KEY                0x80
#define S6D0164_MTP_CTL                 0x81
#define S6D0164_MTP_DATA_WR             0x82
#define S6D0164_PANEL_ID                0x93

void S6D0164::LCD_Write_COM(uint8_t c) {
    _comm->writeCommand16(c << 8);
}

void S6D0164::LCD_Write_COM_DATA(uint8_t c, uint16_t d) {
    _comm->writeCommand16(c << 8);
    _comm->writeData8((d >> 8) & 0xFF);
    _comm->writeData8((d) & 0xFF);
}

void S6D0164::LCD_Write_DATA(uint16_t d) {
    _comm->writeData8((d >> 8) & 0xFF);
    _comm->writeData8((d) & 0xFF);

}

void S6D0164::initializeDevice() 
{
	_comm->initializeDevice();
    _width  = S6D0164::Width;
    _height = S6D0164::Height;

    PMCONbits.ON = 0;
    delay(1);
    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 3;
    PMMODEbits.WAITM = 7;
    PMMODEbits.WAITE = 3;
    PMCONbits.ON = 1;

    LCD_Write_COM_DATA(0x11,0x001A);
    LCD_Write_COM_DATA(0x12,0x3121);
    LCD_Write_COM_DATA(0x13,0x006C);
    LCD_Write_COM_DATA(0x14,0x4249);

    LCD_Write_COM_DATA(0x10,0x0800);
    delay(10);
    LCD_Write_COM_DATA(0x11,0x011A);
    delay(10);
    LCD_Write_COM_DATA(0x11,0x031A);
    delay(10);
    LCD_Write_COM_DATA(0x11,0x071A);
    delay(10);
    LCD_Write_COM_DATA(0x11,0x0F1A);
    delay(10);
    LCD_Write_COM_DATA(0x11,0x0F3A);
    delay(30);

    LCD_Write_COM_DATA(0x01,0x011C);
    LCD_Write_COM_DATA(0x02,0x0100);
    LCD_Write_COM_DATA(0x03,0x1030);
    LCD_Write_COM_DATA(0x07,0x0000);
    LCD_Write_COM_DATA(0x08,0x0808);
    LCD_Write_COM_DATA(0x0B,0x1100);
    LCD_Write_COM_DATA(0x0C,0x0000);

    LCD_Write_COM_DATA(0x0F,0x1401);
    LCD_Write_COM_DATA(0x15,0x0000);
    LCD_Write_COM_DATA(0x20,0x0000);
    LCD_Write_COM_DATA(0x21,0x0000);


    LCD_Write_COM_DATA(0x36,0x00AF);
    LCD_Write_COM_DATA(0x37,0x0000);
    LCD_Write_COM_DATA(0x38,0x00DB);
    LCD_Write_COM_DATA(0x39,0x0000);

    LCD_Write_COM_DATA(0x0F,0x0B01);
    LCD_Write_COM_DATA(0x07,0x0016);
    LCD_Write_COM_DATA(0x07,0x0017);

    LCD_Write_COM(0x22);
}

void S6D0164::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) 
{
    LCD_Write_COM_DATA(0x36,x2);
    LCD_Write_COM_DATA(0x37,x1);
    LCD_Write_COM_DATA(0x38,y2);
    LCD_Write_COM_DATA(0x39,y1);
    LCD_Write_COM_DATA(0x20,x1);
    LCD_Write_COM_DATA(0x21,y1);
    LCD_Write_COM(0x22);
}

void S6D0164::setPixel(int16_t x, int16_t y, uint16_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    LCD_Write_DATA(color);
}

void S6D0164::fillScreen(uint16_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
}

void S6D0164::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            LCD_Write_DATA(color);
		}
	}
}

void S6D0164::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) 
{
    int16_t h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y);

	while (w--) {
        LCD_Write_DATA(color);
	}
}

void S6D0164::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
    int16_t w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x, y+h-1);

	while (h--) {
        LCD_Write_DATA(color);
	}
}

void S6D0164::setRotation(uint8_t m) 
{
    // Use your own rotation settings here!!!!

    LCD_Write_COM(S6D0164_ENTRY_MODE);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			//PORTRAIT
            LCD_Write_DATA(0x1030);
			_width  = S6D0164::Width;
			_height = S6D0164::Height;
			break;
		case 1:
		    //LANDSCAPE
            LCD_Write_DATA(0x1038);
			_width  = S6D0164::Height;
			_height = S6D0164::Width;
			break;
		case 2:	
			//UPSIDE DOWN PORTRAIT
            LCD_Write_DATA(0x1000);
			_width  = S6D0164::Width;
			_height = S6D0164::Height;
			break;
		case 3:
			//UPSIDE DOWN LANDSCAPE
            LCD_Write_DATA(0x1008);
			_width  = S6D0164::Height;
			_height = S6D0164::Width;
			break;
	
    }
}

void S6D0164::invertDisplay(boolean i) 
{
    LCD_Write_COM_DATA(S6D0164_DISPLAY, i ? 0x0017 : 0x0013);
}

void S6D0164::displayOn() 
{
    LCD_Write_COM_DATA(S6D0164_DISPLAY, 0x0013);
}

void S6D0164::displayOff() 
{
    LCD_Write_COM_DATA(S6D0164_DISPLAY, 0x0000);
}

void S6D0164::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
}

void S6D0164::windowData(uint16_t d) {
    LCD_Write_DATA(d);
}

void S6D0164::windowData(uint16_t *d, uint32_t l) {
    _comm->blockData(d, l);
}

void S6D0164::closeWindow() {
}

#endif
