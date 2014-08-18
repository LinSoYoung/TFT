#include <TFT.h>

uint16_t Filter::process(uint16_t incol) {
    uint16_t outcol = function(incol);
    if (_next != NULL) {
        return _next->process(outcol);
    }
    return outcol;
}
