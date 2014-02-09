#include <DSPI.h>
#include <TFT.h>

#include "kitten1.h"
#include "kitten2.h"
#include "kitten3.h"
#include "kitten4.h"

Raw8 kitteh1(kitten1, 160, 128);
Raw8 kitteh2(kitten2, 160, 128);
Raw8 kitteh3(kitten3, 160, 128);
Raw8 kitteh4(kitten4, 160, 128);

#define ADA_SCLK	13
#define ADA_MOSI	11
#define ADA_CS		10
#define ADA_DC		8

// Set up the screen to use
DSPI0 spi;
TFTDSPI mySpi(&spi, ADA_CS, ADA_DC);
ST7735 tft(&mySpi, ST7735::BlackTab);

// Create a framebuffer to store the image while we draw it
uint8_t buffer[ST7735::Height * ST7735::Width];
SRAM sram(buffer, ST7735::Height * ST7735::Width);
Framebuffer fb(ST7735::Height, ST7735::Width, &sram);


void setup() {
	tft.initializeDevice();
	tft.setRotation(3);

	// Start with a black screen
	fb.fillScreen(0);
	fb.setAntiAlias(true);
	tft.update(&fb);
}

void loop()
{
	// Set the palette in the framebuffer to the first image's palette
	fb.loadPalette(kitten1_cmap);
	// Draw the image into the framebuffer
	kitteh1.draw(&fb, 0, 0);
	// Push the contents of the framebuffer out to the display
	tft.update(&fb);
	delay(5000);

	// And do the same with the other images.
	fb.loadPalette(kitten2_cmap);
	kitteh2.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);
	
	fb.loadPalette(kitten3_cmap);
	kitteh3.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);

	fb.loadPalette(kitten4_cmap);
	kitteh4.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);
}
