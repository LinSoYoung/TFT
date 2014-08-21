#ifndef _DATASTORE_H
#define _DATASTORE_H

#include <TFT.h>

class DataBlock;
//class DataWrite;

class DataStore {
	public:
		virtual uint8_t read8(uint32_t addr) = 0;
		virtual uint16_t read16(uint32_t addr) = 0;
		virtual uint32_t read32(uint32_t addr) = 0;
		virtual void read8(uint32_t addr, uint8_t *data, uint32_t len) = 0;
		virtual void read16(uint32_t addr, uint16_t *data, uint32_t len) = 0;
		virtual void read32(uint32_t addr, uint32_t *data, uint32_t len) = 0;
		virtual void write8(uint32_t addr, uint8_t data) = 0;
		virtual void write16(uint32_t addr, uint16_t data) = 0;
		virtual void write32(uint32_t addr, uint32_t data) = 0;
		virtual void write8(uint32_t addr, uint8_t *data, uint32_t len) = 0;
		virtual void write16(uint32_t addr, uint16_t *data, uint32_t len) = 0;
		virtual void write32(uint32_t addr, uint32_t *data, uint32_t len) = 0;

        virtual void setAll8(uint8_t data);
        virtual void setAll16(uint16_t data);
        virtual void setAll32(uint32_t data);

		DataStore() {};
		virtual void initializeDevice() = 0;
		virtual uint32_t size() = 0;

        DataBlock &allocate(uint32_t s);
        void free(DataBlock& b);
};

class DataBlock {
    private:
        uint32_t _start;
        uint32_t _len;
        DataStore *_store;

    public:
        DataBlock(uint32_t start, uint32_t len, DataStore *store) : _start(start), _len(len), _store(store) {}
        uint8_t operator [] (uint32_t a);
        void set(uint32_t a, uint8_t v);
        uint8_t get(uint32_t a);
};

#endif
