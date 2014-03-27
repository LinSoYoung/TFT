
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

void inline __attribute__((alwaysinline)) PICadillo35t::writeCommand(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0000;
    PMDIN = c;
}

void inline __attribute__((alwaysinline)) PICadillo35t::writeData(uint16_t c) {
    while (PMMODEbits.BUSY == 1);
    PMADDR = 0x0001;
    PMDIN = c;
}

//==============================================================
// Initialise HX8357 LCD Driver IC
//==============================================================
void PICadillo35t::initializeDevice() 
{
    PMCONbits.ON = 0;
    asm volatile("nop");

    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;
    PMCONbits.CSF = 0;

    PMAEN = 0x0001; // Enable PMA0 pin for RS pin and CS1 as CS

    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 0;
    PMMODEbits.WAITE = 0;

    //PMADDR = 0; // Set current address to 0
    PMADDR = 0x0000; // Set current address to 0, CS1 Active

    PMCONbits.ON = 1;

    _width  = PICadillo35t::Width;
    _height = PICadillo35t::Height;
	
	colstart = 0;  //NEED TO CONFIRM
    rowstart = 0;  //NEED TO CONFIRM
	
    writeCommand(HX8357_EXIT_SLEEP_MODE); //Sleep Out
    delay(150);
	writeCommand(HX8357_ENABLE_EXTENSION_COMMAND);
	writeData(0xFF);
	writeData(0x83);
	writeData(0x57);
	delay(1);
	writeCommand(HX8357_SET_POWER_CONTROL);
	writeData(0x00);
	writeData(0x12);
	writeData(0x12);
	writeData(0x12);
	writeData(0xC3);
	writeData(0x44);
	delay(1);
	writeCommand(HX8357_SET_DISPLAY_MODE);
	writeData(0x02);
	writeData(0x40);
	writeData(0x00);
	writeData(0x2A);
	writeData(0x2A);
	writeData(0x20);
	writeData(0x91);
	delay(1);
	writeCommand(HX8357_SET_VCOM_VOLTAGE);
	writeData(0x38);
	delay(1);
	writeCommand(HX8357_SET_INTERNAL_OSCILLATOR);
	writeData(0x68);
	writeCommand(0xE3); //Unknown Command
	writeData(0x2F);
	writeData(0x1F);
	writeCommand(0xB5); //Set BGP
	writeData(0x01);
	writeData(0x01);
	writeData(0x67);
	writeCommand(HX8357_SET_PANEL_DRIVING);
	writeData(0x70);
	writeData(0x70);
	writeData(0x01);
	writeData(0x3C);
	writeData(0xC8);
	writeData(0x08);
	delay(1);
	writeCommand(0xC2); // Set Gate EQ
	writeData(0x00);
	writeData(0x08);
	writeData(0x04);
	delay(1);
	writeCommand(HX8357_SET_PANEL_CHARACTERISTIC);
	writeData(0x09);
	delay(1);
	writeCommand(HX8357_SET_GAMMA_CURVE);
	writeData(0x01);
	writeData(0x02);
	writeData(0x03);
	writeData(0x05);
	writeData(0x0E);
	writeData(0x22);
	writeData(0x32);
	writeData(0x3B);
	writeData(0x5C);
	writeData(0x54);
	writeData(0x4C);
	writeData(0x41);
	writeData(0x3D);
	writeData(0x37);
	writeData(0x31);
	writeData(0x21);
	writeData(0x01);
	writeData(0x02);
	writeData(0x03);
	writeData(0x05);
	writeData(0x0E);
	writeData(0x22);
	writeData(0x32);
	writeData(0x3B);
	writeData(0x5C);
	writeData(0x54);
	writeData(0x4C);
	writeData(0x41);
	writeData(0x3D);
	writeData(0x37);
	writeData(0x31);
	writeData(0x21);
	writeData(0x00);
	writeData(0x01);
	delay(1);
	writeCommand(HX8357_SET_PIXEL_FORMAT); //COLMOD RGB888
	writeData(0x55);
	writeCommand(HX8357_SET_ADDRESS_MODE);
	writeData(0x00);
	writeCommand(HX8357_SET_TEAR_ON); //TE ON
	writeData(0x00);
	delay(10);
	writeCommand(HX8357_SET_DISPLAY_ON); //Display On
	delay(10);
	writeCommand(HX8357_WRITE_MEMORY_START); //Write SRAM Data
}

void PICadillo35t::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) 
{
    writeCommand(HX8357_SET_COLUMN_ADDRESS); // Column addr set
    writeData((x0+colstart) >> 8);
    writeData(x0+colstart);     // XSTART 
    writeData((x1+colstart) >> 8);
    writeData(x1+colstart);     // XEND

    writeCommand(HX8357_SET_PAGE_ADDRESS); // Row addr set
    writeData((y0+rowstart) >> 8);
    writeData(y0+rowstart);     // YSTART
    writeData((y1+rowstart) >> 8);
    writeData(y1+rowstart);     // YEND

    writeCommand(HX8357_WRITE_MEMORY_START); //Write SRAM Data
}

void PICadillo35t::setPixel(int16_t x, int16_t y, uint16_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
    PMADDR = 0x0001;
    PMDIN = color;
}

void PICadillo35t::fillScreen(uint16_t color) 
{
	fillRectangle(0, 0,  _width, _height, color);
}

void PICadillo35t::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y+h-1);
	uint8_t hi = color >> 8, lo = color;

    PMADDR = 0x0001;
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            PMDIN = color;
		}
	}
}

void PICadillo35t::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) 
{
    int16_t h = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x+w-1, y);
	uint8_t hi = color >> 8, lo = color;

    PMADDR = 0x0001;
	while (w--) {
		PMDIN = color;
	}
}

void PICadillo35t::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
    int16_t w = 1;
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
	setAddrWindow(x, y, x, y+h-1);
	uint8_t hi = color >> 8, lo = color;

    PMADDR = 0x0001;
	while (h--) {
        PMDIN = color;
	}
}

void PICadillo35t::setRotation(uint8_t m) 
{
	writeCommand(HX8357_SET_ADDRESS_MODE);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			//PORTRAIT
			writeData(0x0000);
			_width  = PICadillo35t::Width;
			_height = PICadillo35t::Height;
			break;
		case 1:
		    //LANDSCAPE
			writeData(0x0060);
			_width  = PICadillo35t::Height;
			_height = PICadillo35t::Width;
			break;
		case 2:	
			//UPSIDE DOWN PORTRAIT
			writeData(0x00C0);
			_width  = PICadillo35t::Width;
			_height = PICadillo35t::Height;
			break;
		case 3:
			//UPSIDE DOWN LANDSCAPE
			writeData(0x00A0);
			_width  = PICadillo35t::Height;
			_height = PICadillo35t::Width;
			break;
	}
}

void PICadillo35t::invertDisplay(boolean i) 
{
	writeCommand(i ? HX8357_INVON : HX8357_INVOFF);
}

void PICadillo35t::displayOn() 
{
	writeCommand(HX8357_DISPLAYON);
}

void PICadillo35t::displayOff() 
{
	writeCommand(HX8357_DISPLAYOFF);
}

void PICadillo35t::openWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    setAddrWindow(x0, y0, x0 + x1 - 1, y0 + y1 - 1);
    PMADDR = 0x0001;
}

void PICadillo35t::windowData(uint16_t d) {
    PMDIN = d;
}

void PICadillo35t::windowData(uint16_t *d, uint32_t l) {
    for (uint32_t i = 0; i < l; i++) {
        PMDIN = d[i];
    }
}

void PICadillo35t::closeWindow() {
}

