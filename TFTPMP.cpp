#include <TFT.h>

/*TFTPMP::TFTPMP(uint8_t rsPin) {	
    _rsPin = rsPin;
	
	TRISDCLR = 0x0800; //(1 << 11); // Set CS pin as Output (CS is RD11)
	LATDCLR = 0x0800; //(1 << 11); // Write CS pin Low (CS is RD11)
}*/

TFTPMP::TFTPMP() {	
}

void TFTPMP::initializeDevice() {

    PMCONbits.ON = 0;
    asm volatile("nop");

    PMCONbits.PTWREN = 1;
    PMCONbits.PTRDEN = 1;
    PMCONbits.CSF = 0;

    /*if (_rsPin != 255) 
	{
        //PMAEN = 0; // Disable PMA0 pin functionality
		PMAEN = 0x0000; // Disable PMA0 pin functionality, CS1 as CS	
		TRISCCLR = (1 << 2); // Set RS pin as Output (RS is RC2)
		LATCCLR = (1 << 2); // Write RS pin Low (RS is RC2)
    } 
	else 
	{
        //PMAEN = 1; // Enable PMA0 pin for RS pin
		PMAEN = 0x0001; // Enable PMA0 pin for RS pin and CS1 as CS
    }*/
	PMAEN = 0x0001; // Enable PMA0 pin for RS pin and CS1 as CS

    PMMODEbits.MODE16 = 1;
    PMMODEbits.MODE = 0b10;
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 0;
    PMMODEbits.WAITE = 0;
    
    //PMADDR = 0; // Set current address to 0
	PMADDR = 0x0000; // Set current address to 0, CS1 Active

    PMCONbits.ON = 1;
}

void TFTPMP::writeCommand8(uint8_t command) {
    writeCommand16(command);
}

void TFTPMP::writeCommand16(uint16_t command) {
    /*if (_rsPin != 255) 
	{
        //digitalWrite(_rsPin, LOW);
		LATCCLR = (1 << 2); // Write RS pin Low (RS is RC2)
    } 
	else 
	{
		//PMADDR = 0; // Command register is at address 0
		PMADDR = 0x0000; // Set current address to 0, CS1 Active
    }*/
    while (PMMODEbits.BUSY == 1);
	PMADDR = 0x0000; // Set current address to 0, CS1 Active
    PMDIN = command;
}

void TFTPMP::writeCommand32(uint32_t command) {
    writeCommand16(command >> 16);
    writeCommand16(command); 
}

void TFTPMP::streamStart() {
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
}

void TFTPMP::streamEnd() {
}

void TFTPMP::writeData8(uint8_t data) {
    writeData16(data);
}

void TFTPMP::writeData16(uint16_t data) {
    /*if (_rsPin != 255) 
	{
        //digitalWrite(_rsPin, HIGH);
		LATCSET = (1 << 2); // Write RS pin High (RS is RC2)
    } else 
	{
        //PMADDR = 1; // Data register is at address 1
		PMADDR = 0x0001; // Data register is at address 1, CS1 Active
    }*/
    while (PMMODEbits.BUSY == 1);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
    PMDIN = data;
}

void TFTPMP::writeData32(uint32_t data) {
    writeData16(data >> 16);
    writeData16(data);
}

void TFTPMP::streamCommand8(uint8_t data) {
    writeCommand8(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
}

void TFTPMP::streamCommand16(uint16_t data) {
    writeCommand16(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
}

void TFTPMP::streamCommand32(uint32_t data) {
    writeCommand32(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
}

void TFTPMP::streamData8(uint8_t data) {
    writeData8(data);
}

void inline TFTPMP::streamData16(uint16_t data) {
    while (PMMODEbits.BUSY == 1);
    PMDIN = data;
}

void TFTPMP::streamData32(uint32_t data) {
    writeData32(data);
}

uint8_t TFTPMP::streamCommand8() { return 0; }
uint16_t TFTPMP::streamCommand16() { return 0; }
uint32_t TFTPMP::streamCommand32() { return 0; }
uint8_t TFTPMP::streamData8() { return 0; }
uint16_t TFTPMP::streamData16() { return 0; }
uint32_t TFTPMP::streamData32() { return 0; }

// One day these three functions will be DMA controlled if DMA is
// available on the chip.

void TFTPMP::blockData(uint8_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData8(data[i]);
    }
}

void TFTPMP::blockData(uint16_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData16(data[i]);
    }
}

void TFTPMP::blockData(uint32_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData32(data[i]);
    }
}

// We don't do any reading yet.  All reads return 0.

uint8_t TFTPMP::readCommand8() {
    return 0;
} 

uint16_t TFTPMP::readCommand16() {
    return 0;
} 

uint32_t TFTPMP::readCommand32() {
    return 0;
} 

uint8_t TFTPMP::readData8() {
    return 0;
} 

uint16_t TFTPMP::readData16() {
    return 0;
} 

uint32_t TFTPMP::readData32() {
    return 0;
} 




