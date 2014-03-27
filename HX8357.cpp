
#include <TFT.h>

//--------------------------------------------------------------------------//
// HX8357 Driver Registers
//--------------------------------------------------------------------------//
#define HX8357_EXIT_SLEEP_MODE          	0x11
#define HX8357_SET_DISPLAY_OFF          	0x28
#define HX8357_SET_DISPLAY_ON           	0x29
#define HX8357_SET_COLUMN_ADDRESS       	0x2A
#define HX8357_SET_PAGE_ADDRESS         	0x2B
#define HX8357_WRITE_MEMORY_START       	0x2C
#define HX8357_READ_MEMORY_START        	0x2E
#define HX8357_SET_TEAR_ON              	0x35
#define HX8357_SET_ADDRESS_MODE         	0x36
#define HX8357_SET_PIXEL_FORMAT         	0x3A
#define HX8357_WRITE_MEMORY_CONTINUE    	0x3C
#define HX8357_READ_MEMORY_CONTINUE     	0x3E
#define HX8357_SET_INTERNAL_OSCILLATOR   	0xB0
#define HX8357_SET_POWER_CONTROL         	0xB1
#define HX8357_SET_DISPLAY_MODE          	0xB4
#define HX8357_SET_VCOM_VOLTAGE         	0xB6
#define HX8357_ENABLE_EXTENSION_COMMAND 	0xB9
#define HX8357_SET_PANEL_DRIVING        	0xC0    // not documented!
#define HX8357_SET_PANEL_CHARACTERISTIC  	0xCC
#define HX8357_SET_GAMMA_CURVE           	0xE0

#define HX8357_INVON 						0x21
#define HX8357_INVOFF						0x20
#define HX8357_DISPLAYOFF					0x28
#define HX8357_DISPLAYON					0x29

//==============================================================
// Initialise HX8357 LCD Driver IC
//==============================================================
void HX8357::initializeDevice() 
{
	_comm->initializeDevice();
    _width  = HX8357::Width;
    _height = HX8357::Height;
	
	colstart = 0;  //NEED TO CONFIRM
    rowstart = 0;  //NEED TO CONFIRM
	
    _comm->writeCommand8(HX8357_EXIT_SLEEP_MODE); //Sleep Out
    delay(150);
	_comm->writeCommand8(HX8357_ENABLE_EXTENSION_COMMAND);
	_comm->writeData8(0xFF);
	_comm->writeData8(0x83);
	_comm->writeData8(0x57);
	delay(1);
	_comm->writeCommand8(HX8357_SET_POWER_CONTROL);
	_comm->writeData8(0x00);
	_comm->writeData8(0x12);
	_comm->writeData8(0x12);
	_comm->writeData8(0x12);
	_comm->writeData8(0xC3);
	_comm->writeData8(0x44);
	delay(1);
	_comm->writeCommand8(HX8357_SET_DISPLAY_MODE);
	_comm->writeData8(0x02);
	_comm->writeData8(0x40);
	_comm->writeData8(0x00);
	_comm->writeData8(0x2A);
	_comm->writeData8(0x2A);
	_comm->writeData8(0x20);
	_comm->writeData8(0x91);
	delay(1);
	_comm->writeCommand8(HX8357_SET_VCOM_VOLTAGE);
	_comm->writeData8(0x38);
	delay(1);
	_comm->writeCommand8(HX8357_SET_INTERNAL_OSCILLATOR);
	_comm->writeData8(0x68);
	_comm->writeCommand8(0xE3); //Unknown Command
	_comm->writeData8(0x2F);
	_comm->writeData8(0x1F);
	_comm->writeCommand8(0xB5); //Set BGP
	_comm->writeData8(0x01);
	_comm->writeData8(0x01);
	_comm->writeData8(0x67);
	_comm->writeCommand8(HX8357_SET_PANEL_DRIVING);
	_comm->writeData8(0x70);
	_comm->writeData8(0x70);
	_comm->writeData8(0x01);
	_comm->writeData8(0x3C);
	_comm->writeData8(0xC8);
	_comm->writeData8(0x08);
	delay(1);
	_comm->writeCommand8(0xC2); // Set Gate EQ
	_comm->writeData8(0x00);
	_comm->writeData8(0x08);
	_comm->writeData8(0x04);
	delay(1);
	_comm->writeCommand8(HX8357_SET_PANEL_CHARACTERISTIC);
	_comm->writeData8(0x09);
	delay(1);
	_comm->writeCommand8(HX8357_SET_GAMMA_CURVE);
	_comm->writeData8(0x01);
	_comm->writeData8(0x02);
	_comm->writeData8(0x03);
	_comm->writeData8(0x05);
	_comm->writeData8(0x0E);
	_comm->writeData8(0x22);
	_comm->writeData8(0x32);
	_comm->writeData8(0x3B);
	_comm->writeData8(0x5C);
	_comm->writeData8(0x54);
	_comm->writeData8(0x4C);
	_comm->writeData8(0x41);
	_comm->writeData8(0x3D);
	_comm->writeData8(0x37);
	_comm->writeData8(0x31);
	_comm->writeData8(0x21);
	_comm->writeData8(0x01);
	_comm->writeData8(0x02);
	_comm->writeData8(0x03);
	_comm->writeData8(0x05);
	_comm->writeData8(0x0E);
	_comm->writeData8(0x22);
	_comm->writeData8(0x32);
	_comm->writeData8(0x3B);
	_comm->writeData8(0x5C);
	_comm->writeData8(0x54);
	_comm->writeData8(0x4C);
	_comm->writeData8(0x41);
	_comm->writeData8(0x3D);
	_comm->writeData8(0x37);
	_comm->writeData8(0x31);
	_comm->writeData8(0x21);
	_comm->writeData8(0x00);
	_comm->writeData8(0x01);
	delay(1);
	_comm->writeCommand8(HX8357_SET_PIXEL_FORMAT); //COLMOD RGB888
	_comm->writeData8(0x55);
	_comm->writeCommand8(HX8357_SET_ADDRESS_MODE);
	_comm->writeData8(0x00);
	_comm->writeCommand8(HX8357_SET_TEAR_ON); //TE ON
	_comm->writeData8(0x00);
	delay(10);
	_comm->writeCommand8(HX8357_SET_DISPLAY_ON); //Display On
	delay(10);
	_comm->writeCommand8(HX8357_WRITE_MEMORY_START); //Write SRAM Data
}

void HX8357::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
{
 _comm->writeCommand8(HX8357_SET_COLUMN_ADDRESS); // Column addr set
 _comm->writeData8((x0+colstart) >> 8);
 _comm->writeData8(x0+colstart);     // XSTART 
 _comm->writeData8((x1+colstart) >> 8);
 _comm->writeData8(x1+colstart);     // XEND

 _comm->writeCommand8(HX8357_SET_PAGE_ADDRESS); // Row addr set
 _comm->writeData8((y0+rowstart) >> 8);
 _comm->writeData8(y0+rowstart);     // YSTART
 _comm->writeData8((y1+rowstart) >> 8);
 _comm->writeData8(y1+rowstart);     // YEND

 _comm->writeCommand8(HX8357_WRITE_MEMORY_START); //Write SRAM Data
}

void HX8357::setPixel(int16_t x, int16_t y, uint16_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
	_comm->writeData16(color);
}

void HX8357::fillScreen(uint16_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
}

void HX8357::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);
	uint8_t hi = color >> 8, lo = color;

    _comm->streamStart();
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            _comm->streamData16(color);
		}
	}
    _comm->streamEnd();
}

void HX8357::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) 
{
    int16_t h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y);
	uint8_t hi = color >> 8, lo = color;

    _comm->streamStart();
	while (w--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void HX8357::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
    int16_t w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x, y+h-1);
	uint8_t hi = color >> 8, lo = color;

    _comm->streamStart();
	while (h--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void HX8357::setRotation(uint8_t m) 
{
	_comm->writeCommand8(HX8357_SET_ADDRESS_MODE);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			//PORTRAIT
			_comm->writeData16(0x0000);
			_width  = HX8357::Width;
			_height = HX8357::Height;
			break;
		case 1:
		    //LANDSCAPE
			_comm->writeData16(0x0060);
			_width  = HX8357::Height;
			_height = HX8357::Width;
			break;
		case 2:	
			//UPSIDE DOWN PORTRAIT
			_comm->writeData16(0x00C0);
			_width  = HX8357::Width;
			_height = HX8357::Height;
			break;
		case 3:
			//UPSIDE DOWN LANDSCAPE
			_comm->writeData16(0x00A0);
			_width  = HX8357::Height;
			_height = HX8357::Width;
			break;
	}
}

void HX8357::invertDisplay(boolean i) 
{
	_comm->writeCommand8(i ? HX8357_INVON : HX8357_INVOFF);
}

void HX8357::displayOn() 
{
	_comm->writeCommand8(HX8357_DISPLAYON);
}

void HX8357::displayOff() 
{
	_comm->writeCommand8(HX8357_DISPLAYOFF);
}

void HX8357::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1, y0 + y1);
    _comm->streamStart();
}

void HX8357::windowData(uint16_t d) {
    _comm->streamData16(d);
}

void HX8357::windowData(uint16_t *d, uint32_t l) {
    _comm->blockData(d, l);
}

void HX8357::closeWindow() {
    _comm->streamEnd();
}

