/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Screen: "Adafruit 1.8" TFT Shield with Joystick and microSD"
 * 
 * Display kittens on the TFT screen in a rotating slideshow.
 * 
 * The kitten images are quite large. Having 4 of them compiles to around 260KB,
 * so you will need one of the larger boards to run this demo as it stands. You
 * can disable some of the images to make it work on a smaller board.
 */

#include <DSPI.h>
#include <TFT.h>

#include "kitten1.h"
#include "kitten2.h"
#include "kitten3.h"
#include "kitten4.h"

BMP kitten1(kitten1_data);
BMP kitten2(kitten2_data);
BMP kitten3(kitten3_data);
BMP kitten4(kitten4_data);

#define ADA_CS		10
#define ADA_DC		8

// Set up the screen to use
DSPI0 spi;
TFTDSPI mySpi(&spi, ADA_CS, ADA_DC, 20000000UL);
ST7735 tft(&mySpi, ST7735::BlackTab);

// Create a framebuffer to store the image while we draw it
uint8_t buffer[ST7735::Height * ST7735::Width];
SRAM sram(buffer, ST7735::Height * ST7735::Width);
Framebuffer332 fb(ST7735::Height, ST7735::Width, &sram);


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
	// Draw the image into the framebuffer
	kitten1.draw(&fb, 0, 0);
	// Push the contents of the framebuffer out to the display
	tft.update(&fb);
	delay(5000);

	// And do the same with the other images.
	kitten2.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);
	
	kitten3.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);

	kitten4.draw(&fb, 0, 0);
	tft.update(&fb);
	delay(5000);
}
