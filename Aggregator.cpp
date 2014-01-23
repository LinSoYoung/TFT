#include <TFT.h>

void Aggregator::fillScreen(uint16_t color) {
    struct AggregatorList *s;
    if (!_displays) {
        return;
    }
    for (s = _displays; s; s = s->next) {
        s->display->fillScreen(color);
    }
}

void Aggregator::invertDisplay(boolean i) {
    struct AggregatorList *s;
    if (!_displays) {
        return;
    }
    for (s = _displays; s; s = s->next) {
        s->display->invertDisplay(i);
    }
}

void Aggregator::setPixel(int16_t x, int16_t y, uint16_t color) {
    struct AggregatorList *s;
    if (!_displays) {
        return;
    }
    for (s = _displays; s; s = s->next) {
        if ((x >= s->x && x < s->x + s->display->getWidth()) && (y >= s->y && y < s->y + s->display->getHeight())) {
            s->display->setPixel(x - s->x, y - s->y, color);
        }
    }
}

void Aggregator::initializeDevice() {
    struct AggregatorList *s;
    for (s = _displays; s; s = s->next) {
        s->display->initializeDevice();
    }
}

void Aggregator::addDisplay(TFT *d, int16_t x, int16_t y) {
    struct AggregatorList *n = (struct AggregatorList *)malloc(sizeof(struct AggregatorList));
    struct AggregatorList *s;

    if (!n) {
        return;
    }

    n->display = d;
    n->x = x;
    n->y = y;
    n->next = NULL;

    if (!_displays) {
        _displays = n;
    } else {
        for (s = _displays; s->next; s = s->next);
        s->next = n;
    }

    if (x + n->display->getWidth() > _width) {
        _width = x + n->display->getWidth();
    }

    if (y + n->display->getHeight() > _height) {
        _height = y + n->display->getHeight();
    }

}

void Aggregator::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
    for (int i = 0; i < w; i++) {
        setPixel(x + i, y, c);
    }
}

void Aggregator::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t c) {
    for (int i = 0; i < h; i++) {
        setPixel(x, y + i, c);
    }
}


void Aggregator::update(Framebuffer *fb) {
    update(fb, 0, 0);
}

void Aggregator::update(Framebuffer *fb, int16_t dx, int16_t dy) {
    struct AggregatorList *s;
    for (s = _displays; s; s = s->next) {
        s->display->update(fb, dx + s->x, dy + s->y);
    }
}
