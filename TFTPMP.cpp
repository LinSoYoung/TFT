#include <TFT.h>

/*TFTPMP::TFTPMP(uint8_t rsPin) {	
    _rsPin = rsPin;
	
	TRISDCLR = 0x0800; //(1 << 11); // Set CS pin as Output (CS is RD11)
	LATDCLR = 0x0800; //(1 << 11); // Write CS pin Low (CS is RD11)
}*/

TFTPMP::TFTPMP() {	
    _lastOp = opWrite;
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
    _lastOp = opWrite;
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
    _lastOp = opWrite;
}

void TFTPMP::writeCommand32(uint32_t command) {
    writeCommand16(command >> 16);
    writeCommand16(command); 
    _lastOp = opWrite;
}

void TFTPMP::streamStart() {
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
}

void TFTPMP::streamEnd() {
}

void TFTPMP::writeData8(uint8_t data) {
    writeData16(data);
    _lastOp = opWrite;
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
    _lastOp = opWrite;
}

void TFTPMP::writeData32(uint32_t data) {
    writeData16(data >> 16);
    writeData16(data);
    _lastOp = opWrite;
}

void TFTPMP::streamCommand8(uint8_t data) {
    writeCommand8(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
    _lastOp = opWrite;
}

void TFTPMP::streamCommand16(uint16_t data) {
    writeCommand16(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
    _lastOp = opWrite;
}

void TFTPMP::streamCommand32(uint32_t data) {
    writeCommand32(data);
	PMADDR = 0x0001; // Data register is at address 1, CS1 Active
    _lastOp = opWrite;
}

void TFTPMP::streamData8(uint8_t data) {
    writeData8(data);
    _lastOp = opWrite;
}

void inline TFTPMP::streamData16(uint16_t data) {
    while (PMMODEbits.BUSY == 1);
    PMDIN = data;
    _lastOp = opWrite;
}

void TFTPMP::streamData32(uint32_t data) {
    writeData32(data);
    _lastOp = opWrite;
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
    _lastOp = opWrite;
}

void TFTPMP::blockData(uint16_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData16(data[i]);
    }
    _lastOp = opWrite;
}

void TFTPMP::blockData(uint32_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData32(data[i]);
    }
    _lastOp = opWrite;
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
    if (_lastOp != opRead) {
        (void)PMDIN;
    }
    while (PMMODEbits.BUSY == 1);
    _lastOp = opRead;
    return PMDIN;
} 

uint16_t TFTPMP::readData16() {
    if (_lastOp != opRead) {
        (void)PMDIN;
    }
    while (PMMODEbits.BUSY == 1);
    _lastOp = opRead;
    return PMDIN;
} 

uint32_t TFTPMP::readData32() {
    uint32_t out = 0;
    if (_lastOp != opRead) {
        (void)PMDIN;
    }
    _lastOp = opRead;
    while (PMMODEbits.BUSY == 1);
    out |= (PMDIN << 16);
    while (PMMODEbits.BUSY == 1);
    out |= PMDIN;
    return out;
} 




