#include <Rambo.h>

Rambo::Rambo(DSPI *spi, uint32_t s, uint8_t cs0, uint8_t cs1, uint8_t cs2, uint8_t cs3, uint8_t cs4, uint8_t cs5, uint8_t cs6, uint8_t cs7, uint8_t cs8, uint8_t cs9, uint8_t cs10, uint8_t cs11, uint8_t cs12, uint8_t cs13, uint8_t cs14, uint8_t cs15) {
    _spi = spi;
    _size = 0;
    _chipsize = s;
    _chips = 0;

    if (cs0 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs0;
        _chips++;
    }
        
    if (cs1 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs1;
        _chips++;
    }

    if (cs2 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs2;
        _chips++;
    }

    if (cs3 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs3;
        _chips++;
    }
        
    if (cs4 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs4;
        _chips++;
    }
        
    if (cs5 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs5;
        _chips++;
    }
        
    if (cs6 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs6;
        _chips++;
    }
        
    if (cs7 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs7;
        _chips++;
    }
        
    if (cs8 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs8;
        _chips++;
    }
        
    if (cs9 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs9;
        _chips++;
    }
        
    if (cs10 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs10;
        _chips++;
    }
        
    if (cs11 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs11;
        _chips++;
    }
        
    if (cs12 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs12;
        _chips++;
    }
        
    if (cs13 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs13;
        _chips++;
    }
        
    if (cs14 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs14;
        _chips++;
    }
        
    if (cs15 != NOT_A_PIN) {
        _size += s;
        _cs[_chips] = cs15;
        _chips++;
    }
}


void Rambo::initializeDevice() {
    _spi->begin();
#ifdef __PIC32MZ__
    _spi->setSpeed(32000000UL);
#else
    _spi->setSpeed(12000000UL);
#endif
    for (int i = 0; i < _chips; i++) {
        pinMode(_cs[i], OUTPUT);
        digitalWrite(_cs[i], HIGH);
    }
}

uint8_t Rambo::read8(uint32_t address) {
    uint8_t b;  

    uint32_t chipno = (address / _chipsize);
    uint32_t chipaddress = address - (chipno * _chipsize);

    digitalWrite(_cs[chipno], LOW);
    _spi->transfer(0x03);
    _spi->transfer((chipaddress >> 16) & 0xFF);
    _spi->transfer((chipaddress >> 8) & 0xFF);
    _spi->transfer((chipaddress >> 0) & 0xFF);
    b = _spi->transfer(0x00);
    digitalWrite(_cs[chipno], HIGH);
    return b;
}

void Rambo::read8(uint32_t address, uint8_t *b, uint32_t len) {
    uint32_t ptr = 0;
    while (len > 0) {
        uint32_t chipno = (address / _chipsize);
        uint32_t chipaddress = address - (chipno * _chipsize);
        uint32_t chipleft = _chipsize - chipaddress;
        
        uint32_t toread = (chipleft < len) ? chipleft : len;
        digitalWrite(_cs[chipno], LOW);
        _spi->transfer(0x03);
        _spi->transfer((chipaddress >> 16) & 0xFF);
        _spi->transfer((chipaddress >> 8) & 0xFF);
        _spi->transfer((chipaddress >> 0) & 0xFF);
        for (uint32_t i = 0; i < toread; i++) {
            b[ptr++] = _spi->transfer(0x00);
        }
        digitalWrite(_cs[chipno], HIGH);
        address += toread;
        len -= toread;
    }
}

void Rambo::write8(uint32_t address, uint8_t b) {

    uint32_t chipno = (address / _chipsize);
    uint32_t chipaddress = address - (chipno * _chipsize);

    digitalWrite(_cs[chipno], LOW);
    _spi->transfer(0x02);
    _spi->transfer((chipaddress >> 16) & 0xFF);
    _spi->transfer((chipaddress >> 8) & 0xFF);
    _spi->transfer((chipaddress >> 0) & 0xFF);
    _spi->transfer(b);
    digitalWrite(_cs[chipno], HIGH);
}

void Rambo::write8(uint32_t address, uint8_t *b, uint32_t len) {
    uint32_t ptr = 0;
    while (len > 0) {
        uint32_t chipno = (address / _chipsize);
        uint32_t chipaddress = address - (chipno * _chipsize);
        uint32_t chipleft = _chipsize - chipaddress;
        
        uint32_t towrite = (chipleft < len) ? chipleft : len;
        digitalWrite(_cs[chipno], LOW);
        _spi->transfer(0x02);
        _spi->transfer((chipaddress >> 16) & 0xFF);
        _spi->transfer((chipaddress >> 8) & 0xFF);
        _spi->transfer((chipaddress >> 0) & 0xFF);
        for (uint32_t i = 0; i < towrite; i++) {
            _spi->transfer(b[ptr++]);
        }
        digitalWrite(_cs[chipno], HIGH);
        address += towrite;
        len -= towrite;
    }
}

uint16_t Rambo::read16(uint32_t address) {
    uint16_t v;
    read8(address << 1, (uint8_t *)&v, 2);
    return v;
}

uint32_t Rambo::read32(uint32_t address) {
    uint32_t v;
    read8(address << 2, (uint8_t *)&v, 4);
    return v;
}

void Rambo::read16(uint32_t address, uint16_t *b, uint32_t len) {
    read8(address << 1, (uint8_t *)b, len << 1);
}

void Rambo::read32(uint32_t address, uint32_t *b, uint32_t len) {
    read8(address << 2, (uint8_t *)b, len << 2);
}

void Rambo::write16(uint32_t address, uint16_t b) {
    write8(address << 1, (uint8_t *)&b, 2);
}

void Rambo::write32(uint32_t address, uint32_t b) {
    write8(address << 2, (uint8_t *)&b, 4);
}

void Rambo::write16(uint32_t address, uint16_t *b, uint32_t len) {
    write8(address << 1, (uint8_t *)b, len << 1);
}

void Rambo::write32(uint32_t address, uint32_t *b, uint32_t len) {
    write8(address << 2, (uint8_t *)b, len << 2);
}

void Rambo::setAll8(uint8_t b) {
    uint32_t len = size();
    uint32_t address = 0;
    while (len > 0) {
        uint32_t chipno = (address / _chipsize);
        uint32_t chipaddress = address - (chipno * _chipsize);
        uint32_t chipleft = _chipsize - chipaddress;
        
        uint32_t towrite = (chipleft < len) ? chipleft : len;
        digitalWrite(_cs[chipno], LOW);
        _spi->transfer(0x02);
        _spi->transfer((chipaddress >> 16) & 0xFF);
        _spi->transfer((chipaddress >> 8) & 0xFF);
        _spi->transfer((chipaddress >> 0) & 0xFF);
        for (uint32_t i = 0; i < towrite; i++) {
            _spi->transfer(b);
        }
        digitalWrite(_cs[chipno], HIGH);
        address += towrite;
        len -= towrite;
    }
}

void Rambo::setAll16(uint16_t b) {
    uint32_t len = size();
    uint32_t address = 0;
    while (len > 0) {
        uint32_t chipno = (address / _chipsize);
        uint32_t chipaddress = address - (chipno * _chipsize);
        uint32_t chipleft = _chipsize - chipaddress;
        
        uint32_t towrite = (chipleft < len) ? chipleft : len;
        digitalWrite(_cs[chipno], LOW);
        _spi->transfer(0x02);
        _spi->transfer((chipaddress >> 16) & 0xFF);
        _spi->transfer((chipaddress >> 8) & 0xFF);
        _spi->transfer((chipaddress >> 0) & 0xFF);
        for (uint32_t i = 0; i < towrite; i+=2) {
            _spi->transfer(b & 0xFF);
            _spi->transfer(b >> 8);
        }
        digitalWrite(_cs[chipno], HIGH);
        address += towrite;
        len -= towrite;
    }
}

void Rambo::setAll32(uint32_t b) {
    uint32_t len = size();
    uint32_t address = 0;
    while (len > 0) {
        uint32_t chipno = (address / _chipsize);
        uint32_t chipaddress = address - (chipno * _chipsize);
        uint32_t chipleft = _chipsize - chipaddress;
        
        uint32_t towrite = (chipleft < len) ? chipleft : len;
        digitalWrite(_cs[chipno], LOW);
        _spi->transfer(0x02);
        _spi->transfer((chipaddress >> 16) & 0xFF);
        _spi->transfer((chipaddress >> 8) & 0xFF);
        _spi->transfer((chipaddress >> 0) & 0xFF);
        for (uint32_t i = 0; i < towrite; i+=4) {
            _spi->transfer(b & 0xFF);
            _spi->transfer(b >> 8);
            _spi->transfer(b >> 16);
            _spi->transfer(b >> 32);
        }
        digitalWrite(_cs[chipno], HIGH);
        address += towrite;
        len -= towrite;
    }
}
