#ifndef _FILTER_H
#define _FILTER_H

#include <TFT.h>

class Filter; 

class Filter {
    protected:
        Filter *_next;
    public:
        Filter() : _next(NULL) {};
        uint16_t process(uint16_t);
        virtual uint16_t function(uint16_t) = 0;
        void chain(Filter &f) { _next = &f; }
        void chain(Filter *f) { _next = f; }
        void endChain() { _next = NULL; }
};

#include <AdjustHSV.h>
#include <Brightness.h>
#include <Contrast.h>
#include <Monochrome.h>
#include <Tint.h>

#endif
