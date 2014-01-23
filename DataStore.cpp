#include <TFT.h>

uint8_t DataBlock::operator [] (uint32_t a) {
    a = a % _len;
    return _store->read8(_start + a);
}

uint8_t DataBlock::get(uint32_t a) {
    a = a % _len;
    return _store->read8(_start + a);
}

void DataBlock::set(uint32_t a, uint8_t v) {
    a = a % _len;
    _store->write8(_start + a, v);
}

DataBlock &DataStore::allocate(uint32_t size) {
    uint32_t start = 0;
    DataBlock s(start, size, this);
    return s;
}

void DataStore::free(DataBlock &b) {
    delete &b;
}
