#include <TFT.h>

PICadillo35t tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

class Button {
	private:
		int16_t _x;
		int16_t _y;
		int16_t _w;
		int16_t _h;
		TFT *_dev;
		Touch *_ts;

		uint16_t _tw;
		uint16_t _th;

		char *_txt;
		const uint8_t *_font;

		uint16_t _bg;
		uint16_t _fg;
		boolean _lastPressed;
		boolean _pressed;
		uint16_t _bevel;
		
	public:
		Button(TFT &dev, Touch &ts, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t bg, uint16_t fg, char *txt, const uint8_t *font) :
			_dev(&dev), _ts(&ts), _x(x), _y(y), _w(w), _h(h), _bg(bg), _fg(fg), _txt(txt), _font(font), _bevel(2) {}
		boolean render();
		void setBevel(uint16_t b) { _bevel = b; }
};

boolean Button::render() {
	_dev->setFont(_font);
	int _tw = _dev->stringWidth(_txt);
	int _th = _dev->stringHeight(_txt);
	
	if (_ts->isPressed() != _lastPressed) {
		_lastPressed = _ts->isPressed();
		if (_lastPressed) {
			if (_ts->x() > _x && _ts->y() > _y && _ts->x() < _x+_w & _ts->y() < _y+_h) {
				_pressed = true;
			} else {
				_pressed = false;
			}
		} else {
			_pressed = false;
		}
	}
	for (int i = 0; i < _bevel; i++) {
		_dev->drawLine(_x,      _y+i,    _x+_w-i-1, _y+i,    _pressed ? Color::Gray45 : Color::Gray85);
		_dev->drawLine(_x+i,    _y+_h-i-1, _x+_w-1,   _y+_h-i-1, _pressed ? Color::Gray85 : Color::Gray45);
		_dev->drawLine(_x+i,    _y,      _x+i,    _y+_h-i-1, _pressed ? Color::Gray45 : Color::Gray85);
		_dev->drawLine(_x+_w-i-1, _y+i,    _x+_w-i-1, _y+_h-1,   _pressed ? Color::Gray85 : Color::Gray45);
	}
	_dev->fillRectangle(_x+_bevel,     _y+_bevel,    _w-_bevel-_bevel,  _h/2-_bevel-_th/2, _bg);
	_dev->fillRectangle(_x+_bevel,     _y+_h/2+_th/2, _w-_bevel-_bevel,  _h/2-_bevel-_th/2, _bg);
	_dev->fillRectangle(_x+_bevel,     _y+_h/2-_th/2, _w/2-_tw/2-_bevel,   _th, _bg);
	_dev->fillRectangle(_x+_w/2+_tw/2, _y+_h/2-_th/2, _w/2-_tw/2-_bevel, _th, _bg);
	_dev->setTextColor(_fg, _bg);
	_dev->setCursor(_x + _w/2 - _tw/2, _y + _h/2 - _th/2);
	_dev->print(_txt);
	return _pressed;	
}

Button on(tft, ts, 0, 100, 160, 100, Color::Gray75, Color::DarkGreen, "ON", Fonts::Liberation16);
Button off(tft, ts, 160, 100, 160, 100, Color::Gray75, Color::Red, "OFF", Fonts::Liberation16);

Button a1(tft, ts, 0, 200, 80, 80, Color::Gray75, Color::White, "C", Fonts::Liberation16);
Button a2(tft, ts, 80, 200, 80, 80, Color::Gray75, Color::White, "D", Fonts::Liberation16);
Button a3(tft, ts, 160, 200, 80, 80, Color::Gray75, Color::White, "E", Fonts::Liberation16);
Button a4(tft, ts, 240, 200, 80, 80, Color::Gray75, Color::White, "F", Fonts::Liberation16);

Button b1(tft, ts, 0, 280, 80, 80, Color::Gray75, Color::White, "G", Fonts::Liberation16);
Button b2(tft, ts, 80, 280, 80, 80, Color::Gray75, Color::White, "A", Fonts::Liberation16);
Button b3(tft, ts, 160, 280, 80, 80, Color::Gray75, Color::White, "B", Fonts::Liberation16);
Button b4(tft, ts, 240, 280, 80, 80, Color::Gray75, Color::White, "C", Fonts::Liberation16);

void setup() {
	analogWrite(PIN_BACKLIGHT, 255);
	tft.initializeDevice();
	ts.initializeDevice();
	tft.fillScreen(Color::Black);
	tft.setFont(Fonts::Default);
	tft.setTextColor(Color::White);
	on.setBevel(4);
	off.setBevel(4);
	pinMode(PIN_AUDENB, OUTPUT);
	digitalWrite(PIN_AUDENB, HIGH);
}

void loop() {
	ts.sample();
	static boolean onoff = false;
	boolean onval = on.render();
	boolean offval = off.render();

	if (a1.render()) tone(PIN_AUDIO, 262, 50);
	if (a2.render()) tone(PIN_AUDIO, 294, 50);
	if (a3.render()) tone(PIN_AUDIO, 330, 50);
	if (a4.render()) tone(PIN_AUDIO, 349, 50);

	if (b1.render()) tone(PIN_AUDIO, 392, 50);
	if (b2.render()) tone(PIN_AUDIO, 440, 50);
	if (b3.render()) tone(PIN_AUDIO, 494, 50);
	if (b4.render()) tone(PIN_AUDIO, 523, 50);

	if (onval && (onoff == false)) {
		onoff = true;
		digitalWrite(PIN_AUDENB, LOW);
		tone(PIN_AUDIO, 1000, 10);
		delay(10);
	}
	if (offval && (onoff == true)) {
		onoff = false;
		tone(PIN_AUDIO, 800, 10);
		delay(10);
		digitalWrite(PIN_AUDENB, HIGH);
	}
	tft.fillRectangle(0, 0, 320, 50, onoff ? Color::Green : Color::Red);
	tft.fillRectangle(0, 60, ts.pressure(), 5, Color::Yellow);
	tft.fillRectangle(ts.pressure(), 60, 320-ts.pressure(), 5, Color::Black);
}
\