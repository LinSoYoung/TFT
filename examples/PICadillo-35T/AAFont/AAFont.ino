#include <TFT.h>

TFTPMP pmp;
HX8357 tft(&pmp);

 
void setup()
{
	analogWrite(PIN_BACKLIGHT, 255);
	tft.initializeDevice();
	tft.setRotation(1);
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Liberation30);
	tft.setTextColor(Color::Red);
	tft.setCursor(10, 150);
	tft.print("This is a font test");
	tft.setFont(Fonts::Liberation10);
	tft.setTextColor(Color::Goldenrod);
	tft.setCursor(10, 280);
	tft.print("Liberation is the first of the 2-bits-per-pixel");
	tft.setCursor(10, 300);
	tft.print("anti-aliased fonts in the TFT library.");
	tft.setFont(Fonts::Liberation30);
	tft.setTextColor(Color::Green);
}
 
void loop()
{
	tft.setCursor(100, 50);
	tft.print(millis());
//	delay(100);
}