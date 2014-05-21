#include <TFT.h>
#include <BMPFile.h>
#include <Widgets.h>

PICadillo35t tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

const int btnSize = 64;

const int backlight = PIN_BACKLIGHT;

uint16_t colors[8] = {
	Color::Black,
	Color::Red,
	Color::Green,
	Color::Yellow,
	Color::Blue,
	Color::Magenta,
	Color::Cyan,
	Color::White
};

uint16_t color = 1;
uint16_t size = 2;

twButton cont(tft, ts, 75, 300, 170, 75, "CONTINUE");

void error(char *message) {
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);
	tft.fillScreen(Color::Black);
	tft.setCursor(0, 0);
	tft.print(message);
	fadeUp();
	while(1);
}

void setup() {
	analogWrite(backlight, 0);
	ts.initializeDevice();

	// These set the touch screen resolution.
	ts.scaleX(4.1);
	ts.scaleY(3.2);

	tft.initializeDevice();
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);
	tft.fillScreen(Color::Black);

	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::White, Color::Black);	
	tft.setCursor(0, 0);
	if (!SD.begin(PIN_SD_SS)) {
		error("Unable to initialize SD card!");
	}

	cont.setBevel(4);
	cont.setTextColor(Color::Red);
	cont.setFont(Fonts::Liberation20);
	drawLogo();
	tinkle();
	prims();
	scribble();
}

void tinkle() {
	pinMode(PIN_AUDENB, OUTPUT);
	digitalWrite(PIN_AUDENB, LOW);
	for (int i = 0; i < 4; i++) {
		tone(PIN_AUDIO, 262, 50);
		delay(100);
		tone(PIN_AUDIO, 294, 50);
		delay(100);
		tone(PIN_AUDIO, 330, 50);
		delay(100);
		tone(PIN_AUDIO, 392, 50);
		delay(100);
		tone(PIN_AUDIO, 440, 50);
		delay(100);
	}
    pinMode(PIN_AUDENB, OUTPUT);
    digitalWrite(PIN_AUDENB, HIGH);
}

void doContinue() {
	cont.render();
	fadeUp();
	ts.sample();
	int lx = ts.x();
	int ly = ts.y();
	while (cont.render() != true) {

		tft.fillTriangle(0, ly-4, 4, ly, 0, ly+4, Color::Gray40);		
		tft.fillTriangle(319, ly-4, 319-4, ly, 319, ly+4, Color::Gray40);		

		tft.fillTriangle(lx-4, 0, lx, 4, lx+4, 0, Color::Gray40);		
		tft.fillTriangle(lx-4, 479, lx, 479-4, lx+4, 479, Color::Gray40);		

		ts.sample();
		lx = ts.x();
		ly = ts.y();
		tft.fillTriangle(0, ly-4, 4, ly, 0, ly+4, Color::White);		
		tft.fillTriangle(319, ly-4, 319-4, ly, 319, ly+4, Color::White);		

		tft.fillTriangle(lx-4, 0, lx, 4, lx+4, 0, Color::White);		
		tft.fillTriangle(lx-4, 479, lx, 479-4, lx+4, 479, Color::White);		
	}
	pinMode(PIN_AUDENB, OUTPUT);
	digitalWrite(PIN_AUDENB, HIGH);
	fadeDown();	
}

void fadeUp() {
	for (int i = 0; i < 255; i++) {
		analogWrite(backlight, i);
		delay(1);
	}	
}

void fadeDown() {
	for (int i = 0; i < 255; i++) {
		analogWrite(backlight, 255 - i);
		delay(1);
	}	
}

void drawLogo() {
	File f = SD.open("/4dlogo.bmp");
	if (!f) {
		tft.print("Unable to open image file!!!");
		while(1);
	}
	tft.fillScreen(Color::Gray40);
	BMPFile bmp(f);
	bmp.draw(&tft, 10, 100);
	doContinue();
	tft.fillScreen(Color::Black);
}

void loop() { }

void scribble() {
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Liberation32);
	int tw = tft.stringWidth("DRAW!");
	tft.setCursor(160 - (tw/2), 220);
	tft.setTextColor(Color::White, Color::Black);	
	tft.print("DRAW!");
	fadeUp();
	while (1) {
		ts.sample();
	
		if (ts.isPressed()) {
			tft.fillCircle(ts.x(), ts.y(), 4, Color::Red);
		}
	}
}

void prims() {
	for (int i = 0; i < 1000; i++) {
		int primno = rand() % 7;
	
		switch (primno) {
			case 0:
				drawLine();
				break;
			case 1:
				drawRectangle();
				break;
			case 2:
				drawCircle();
				break;
			case 3:
				drawFilledRectangle();
				break;
			case 4:
				drawFilledCircle();
				break;
			case 5:
				drawRoundedRectangle();
				break;
			case 6:
				drawFilledRoundedRectangle();
				break;
		}
	}
	doContinue();
	tft.fillScreen(Color::Black);
}

void drawLine() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int endX = rand() % tft.getWidth();
	int endY = rand() % tft.getHeight();
	uint16_t color = rand();

	tft.drawLine(startX, startY, endX, endY, color);
}

void drawRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.drawRectangle(startX, startY, width, height, color);
}

void drawCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.drawCircle(centerX, centerY, radius, color);
}

void drawFilledRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() % tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	uint16_t color = rand();

	tft.fillRectangle(startX, startY, width, height, color);
}

void drawFilledCircle() {
	int centerX = rand() % tft.getWidth();
	int centerY = rand() % tft.getHeight();
	int radius = rand() % tft.getWidth() / 4;
	uint16_t color = rand();

	tft.fillCircle(centerX, centerY, radius, color);
}

void drawRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.drawRoundRect(startX, startY, width, height, radius, color);
}

void drawFilledRoundedRectangle() {
	int startX = rand() % tft.getWidth();
	int startY = rand() & tft.getHeight();
	int width = rand() % tft.getWidth() / 2;
	int height = rand() % tft.getHeight() / 2;
	int radius = rand() % 10;
	width += radius * 2;
	height += radius * 2;
	uint16_t color = rand();

	tft.fillRoundRect(startX, startY, width, height, radius, color);
}

