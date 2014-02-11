TFT Base Class Function List
============================

Draw a hollow circle centered at *x0,y0* with a radius of *r* in color *color*.

    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

Draw a filled circle centered at *x0,y0* with a radius of *r* in color *color*.

    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

Draw a line from point *x0,y0* to point *x1,y1* in color *color*.

    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

Draw a hollow rectangle from point *x,y* with width *w* and height *h* in color *color*.

    void drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

Draw a filled rectangle from point *x,y* with width *w* and height *h* in color *color*.

    void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

Draw a hollow rectangle from point *x,y* with width *w* and height *h* in color *color*.  The corners are rounded off with a radius of *r*.

    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);

Draw a filled rectangle from point *x,y* with width *w* and height *h* in color *color*.  The corners are rounded off with a radius of *r*.

    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);

Draw a hollow triangle with points at *x0,y0*, *x1,y1* and *x2,y2* in color *color*.

    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

Draw a filled triangle with points at *x0,y0*, *x1,y1* and *x2,y2* in color *color*.

    void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

Set the text cursor to point *x,y*.

    void setCursor(int16_t x, int16_t y);

Set the text foreground color to *c*.

    void setTextColor(uint16_t c);

Set the text foreeground color to *fg* and background color to *bg*.  If both *fg* and *bg* are the same the background becomes transparent.

    void setTextColor(uint16_t fg, uint16_t bg);

Return the current text foreground color.

    uint16_t getTextColor();

Swap the text foreground and background colors.

    void invertTextColor();

Enable or disable text line wrapping (default: enabled).

    void setTextWrap(boolean w);

Convert red/green/blue values (0-255) into a 16-bit 565 color value.

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

Fill the entire screen with *color*.

    void fillScreen(uint16_t color);

Set the current text font to *f*.  See Fonts.h for a full list.

    void setFont(const uint8_t *f);

Set a single pixel on the screen at point *x,y* to *color*.

    void setPixel(int16_t x, int16_t y, uint16_t color);

Draw a horizontal line starting at point *x,y* and extending right for a width of *w* pixels in color *color*.

    void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);

Draw a vertical line starting at point *x,y* and extending down for a height of *h* pixels in color *color*.

    void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);

Configure the device and any devices it depends upon.

    void initializeDevice();

Turn on the display (if supported by the display).

    void displayOn();

Turn off the display (if supported by the display).

    void displayOff();

Enable or disable color inversion on the display (if supported by the display).

    void invertDisplay(boolean i);

Update the display contents with the contents of framebuffer *fb*.

    void update(Framebuffer *fb);

Update the display contents with the contents of framebuffer *fb* at an offset of *dx,dy*.

    void update(Framebuffer *fb, int16_t dx, int16_t dy);

Return the width in pixels of a string *text* rendered in the currently selected font.

    uint16_t stringWidth(char *text);

Return the height in pixels of a string *text* rendered in the currently selected font.

    uint16_t stringHeight(char *text);

Return the color at point *x,y* on the screen ignoring any additional rendering layers.

    uint16_t bgColorAt(int16_t x, int16_t y);

Return the color at point *x,y* on the screen taking into account any extra rendering layers.

    uint16_t colorAt(int16_t x, int16_t y);

Write a character *c* to the screen at the current text cursor position (used by print()).

    void write(uint8_t c);

Draw a character *c* at location *x,y* in foreground and background colors *fg* and *bg*.

    uint8_t drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);

Return the width of the display.

    uint16_t getWidth();

Return the height of the display.

    uint16_t getHeight();

Convert a 16-bit 565 colour value into an XYZ 3D color space representation.

    point3d rgb2xyz(uint16_t c);

Convert an XYZ 3D color space color into an LAB color.

    point3d xyz2lab(point3d c);

Calculate the Delta-E distance between two LAB colors in 3D color space.

    float deltaE(point3d labA, point3d labB);

Calculate the Delta-Orth distance between two 565 colors in 2D color space.

    uint32_t deltaOrth(uint16_t c1, uint16_t c2);

Convert a 16-bit 565 color into a 24-bit HSV color.

    uint32_t rgb2hsv(uint16_t rgb);

