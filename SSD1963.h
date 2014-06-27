#ifndef _SSD1963_H_
#define _SSD1963_H_

#include <TFT.h>

#define SSD1963_NOP                     0x00
#define SSD1963_SoftReset               0x01
#define SSD1963_GetPowerMode            0x0A
#define SSD1963_GetAddressMode          0x0B
#define SSD1963_GetDisplayMode          0x0D
#define SSD1963_GetTearEffectsStatus    0x0E
#define SSD1963_EnterSleepMode          0x10
#define SSD1963_ExitSleepMode           0x11
#define SSD1963_EnterPartialMode        0x12
#define SSD1963_EnterNormalMode         0x13
#define SSD1963_ExitInvertMode          0x20
#define SSD1963_EnterInvertMode         0x21
#define SSD1963_SetGammaCurve           0x26
#define SSD1963_SetDisplayOff           0x28
#define SSD1963_SetDisplayOn            0x29
#define SSD1963_SetColumnAddress        0x2A
#define SSD1963_SetPageAddress          0x2B
#define SSD1963_WriteMemoryStart        0x2C
#define SSD1963_ReadMemoryStart         0x2E
#define SSD1963_SetPartialArea          0x30
#define SSD1963_SetScrollArea           0x33
#define SSD1963_SetTearOff              0x34
#define SSD1963_SetTearOn               0x35
#define SSD1963_SetAddressMode          0x36
#define SSD1963_SetScrollStart          0x37
#define SSD1963_ExitIdleMode            0x38
#define SSD1963_EnterIdleMode           0x39
#define SSD1963_WriteMemoryContinue     0x3C
#define SSD1963_ReadMemoryContinue      0x3E
#define SSD1963_SetTearScanline         0x44
#define SSD1963_GetScanline             0x45
#define SSD1963_ReadDDB                 0xA1
#define SSD1963_SetLCDMode              0xB0
#define SSD1963_GetLCDMode              0xB1
#define SSD1963_SetHoriPeriod           0xB4
#define SSD1963_GetHoriPeriod           0xB5
#define SSD1963_SetVertPeriod           0xB6
#define SSD1963_GetVertPeriod           0xB7
#define SSD1963_SetGPIOConf             0xB8
#define SSD1963_GetGPIOConf             0xB9
#define SSD1963_SetGPIOValue            0xBA
#define SSD1963_GetGPIOValue            0xBB
#define SSD1963_SetPostProc             0xBC
#define SSD1963_GetPostProc             0xBD
#define SSD1963_SetPWMConf              0xBE
#define SSD1963_GetPWMConf              0xBF
#define SSD1963_SetLCDGen0              0xC0
#define SSD1963_GetLCDGen0              0xC1
#define SSD1963_SetLCDGen1              0xC2
#define SSD1963_GetLCDGen1              0xC3
#define SSD1963_SetLCDGen2              0xC4
#define SSD1963_GetLCDGen2              0xC5
#define SSD1963_SetLCDGen3              0xC6
#define SSD1963_GetLCDGen3              0xC7
#define SSD1963_SetGPIO0Rop             0xC8
#define SSD1963_GetGPIO0Rop             0xC9
#define SSD1963_SetGPIO1Rop             0xCA
#define SSD1963_GetGPIO1Rop             0xCB
#define SSD1963_SetGPIO2Rop             0xCC
#define SSD1963_GetGPIO2Rop             0xCD
#define SSD1963_SetGPIO3Rop             0xCE
#define SSD1963_GetGPIO3Rop             0xCF
#define SSD1963_SetDBCConf              0xD0
#define SSD1963_GetDBCConf              0xD1
#define SSD1963_SetDBCTh                0xD4
#define SSD1963_GetDBCTh                0xD5
#define SSD1963_SetPLL                  0xE0
#define SSD1963_SetPLLMN                0xE2
#define SSD1963_GetPLLMN                0xE3
#define SSD1963_GetPLLStatus            0xE4
#define SSD1963_SetDeepSleep            0xE5
#define SSD1963_SetLShiftFreq           0xE6
#define SSD1963_GetLShiftFreq           0xE7
#define SSD1963_SetPixelDataInterface   0xF0
#define SSD1963_GetPixelDataInterface   0xF1

class SSD1963 : public TFT {

    private:
		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

	public:
        /*! The width of the screen is 800 pixels */
        static const uint16_t Width      = 800;
        /*! The height of the screen is 480 pixels */
        static const uint16_t Height     = 480;

		SSD1963(TFTCommunicator *comms) : TFT(comms) {}
		SSD1963(TFTCommunicator &comms) : TFT(comms) {}

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        /*! Not currently implemented */
        void displayOn() {} 
        /*! Not currently implemented */
        void displayOff() {} 

        void initializeDevice();

};

#endif
