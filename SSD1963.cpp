#include <TFT.h>

inline uint16_t swapcolor(uint16_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

const uint16_t   HDP=799;
const uint16_t   HT=928;
const uint16_t   HPS=46;
const uint16_t   LPS=15;
const uint8_t    HPW=48;

const uint16_t   VDP=479;
const uint16_t   VT=525;
const uint16_t   VPS=16;
const uint16_t   FPS=8;
const uint8_t    VPW=16;


void SSD1963::initializeDevice() {
    _comm->initializeDevice();
    _width  = SSD1963::Width;
    _height = SSD1963::Height;

    _comm->streamStart();
    _comm->streamCommand16(SSD1963_SetPLLMN);
        _comm->streamData16(0x0023);        //N=0x36 for 6.5M, 0x23 for 10M crystal
        _comm->streamData16(0x0002);
        _comm->streamData16(0x0004);
    _comm->streamCommand16(SSD1963_SetPLL);  // PLL enable
        _comm->streamData16(0x0001);
    delay(1);
    _comm->streamCommand16(SSD1963_SetPLL);
        _comm->streamData16(0x0003);
    delay(5);
    _comm->streamCommand16(SSD1963_SoftReset);  // software reset
    delay(5);
    _comm->streamCommand16(SSD1963_SetLShiftFreq); //PLL setting for PCLK, depends on resolution
        _comm->streamData16(0x0003);
        _comm->streamData16(0x00ff);
        _comm->streamData16(0x00ff);

    _comm->streamCommand16(SSD1963_SetLCDMode);
        _comm->streamData16(0x0000);
        _comm->streamData16(0x0000);
        _comm->streamData16((HDP>>8)&0X00FF);  //Set HDP
        _comm->streamData16(HDP&0X00FF);
        _comm->streamData16((VDP>>8)&0X00FF);  //Set VDP
        _comm->streamData16(VDP&0X00FF);
        _comm->streamData16(0x0000);

    _comm->streamCommand16(SSD1963_SetHoriPeriod);
        _comm->streamData16((HT>>8)&0X00FF);  //Set HT
        _comm->streamData16(HT&0X00FF);
        _comm->streamData16((HPS>>8)&0X00FF);  //Set HPS
        _comm->streamData16(HPS&0X00FF);
        _comm->streamData16(HPW);              //Set HPW
        _comm->streamData16((LPS>>8)&0X00FF);  //Set HPS
        _comm->streamData16(LPS&0X00FF);
        _comm->streamData16(0x0000);

    _comm->streamCommand16(SSD1963_SetVertPeriod); 
        _comm->streamData16((VT>>8)&0X00FF);   //Set VT
        _comm->streamData16(VT&0X00FF);
        _comm->streamData16((VPS>>8)&0X00FF);  //Set VPS
        _comm->streamData16(VPS&0X00FF);
        _comm->streamData16(VPW);              //Set VPW
        _comm->streamData16((FPS>>8)&0X00FF);  //Set FPS
        _comm->streamData16(FPS&0X00FF);

    _comm->streamCommand16(SSD1963_SetGPIOValue);
        _comm->streamData16(0x0005);    //GPIO[3:0] out 1

    _comm->streamCommand16(SSD1963_SetGPIOConf);
        _comm->streamData16(0x0007);    //GPIO3=input, GPIO[2:0]=output
        _comm->streamData16(0x0001);    //GPIO0 normal

    _comm->streamCommand16(SSD1963_SetAddressMode); //rotation
        _comm->streamData16(0x0000);

    _comm->streamCommand16(SSD1963_SetPixelDataInterface);
        _comm->streamData16(0x0003);

    delay(5);

    _comm->streamCommand16(SSD1963_SetDisplayOn);
    _comm->streamCommand16(SSD1963_SetDBCConf);
        _comm->streamData16(0x000d);
    _comm->streamEnd();
}

void SSD1963::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

    uint16_t x0a, x1a, y0a, y1a;

    switch(rotation) {
        case 1:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
  
            x0 = y0a;
            x1 = y1a;
            y0 = _width - x1a;
            y1 = _width - x0a;
            break;
        case 2:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
        
            x0 = _width - x1a;
            x1 = _width - x0a;
            y0 = _height - y1a;
            y1 = _height - y0a;
            break;
  

        case 3:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;

            x0 = _height - y1a;
            x1 = _height - y0a;
            y0 = x0a;
            y1 = x1a;
            break;
    }

    _comm->streamCommand16(SSD1963_SetColumnAddress);
    _comm->streamData16((x0 >> 8) & 0xFF);
    _comm->streamData16(x0 & 0xFF);
    _comm->streamData16((x1 >> 8) & 0xFF);
    _comm->streamData16(x1 & 0xFF);
    _comm->streamCommand16(SSD1963_SetPageAddress);
    _comm->streamData16((y0 >> 8) & 0xFF);
    _comm->streamData16(y0 & 0xFF);
    _comm->streamData16((y1 >> 8) & 0xFF);
    _comm->streamData16(y1 & 0xFF);
    _comm->streamCommand16(SSD1963_WriteMemoryStart);

}

void SSD1963::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    _comm->streamStart();
	setAddrWindow(x,y,x,y);
	_comm->streamData16(color);
    _comm->streamEnd();
}

void SSD1963::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void SSD1963::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (!clipToScreen(x, y, w, h)) {
        return;
    }
    _comm->streamStart();
	setAddrWindow(x, y, x+w-1, y+h-1);
	for(uint32_t i = 0; i < w * h; i++) {
        _comm->streamData16(color);
	}
    _comm->streamEnd();
}

void SSD1963::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    if ((y < 0) || (y >= _height) || (w <= 0)) {
        return;
    }

    if (x < 0) {
        w += x;
        x = 0;
        if (w <= 0) {
            return;
        }
    }

    if (x >= _width) {
        return;
    }

    if (x + w >= _width) {
        w = _width-x;
        if (w <= 0) {
            return;
        }
    }

    _comm->streamStart();
	setAddrWindow(x, y, x+w-1, y);
	while (w--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void SSD1963::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if ((x < 0) || (x >= _width) || (h <= 0)) {
        return;
    }

    if (y < 0) {
        h += y;
        y = 0;
        if (h <= 0) {
            return;
        }
    }

    if (y >= _height) {
        return;
    }

    if (y + h >= _height) {
        h = _height-y;
        if (h <= 0) {
            return;
        }
    }

    _comm->streamStart();
	setAddrWindow(x, y, x, y+h-1);
	while (h--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

#define SSD1963_EMODE 0x0003

#define SSD1963_TRI 0x8000
#define SSD1963_DFM 0x4000
#define SSD1963_BGR 0x1000
#define SSD1963_HWM 0x0200
#define SSD1963_ORG 0x0080
#define SSD1963_ID0 0x0000
#define SSD1963_ID1 0x0010
#define SSD1963_ID2 0x0020
#define SSD1963_ID3 0x0030
#define SSD1963_AM  0x0008

void SSD1963::setRotation(uint8_t m) {
	rotation = m % 4; // can't be higher than 3
}

void SSD1963::invertDisplay(boolean i) {
	_comm->writeCommand16(i ? SSD1963_EnterInvertMode : SSD1963_ExitInvertMode);
}

