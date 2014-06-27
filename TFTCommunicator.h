#ifndef _TFT_COMMUNICATOR_H
#define _TFT_COMMUNICATOR_H

#include <TFT.h>

/*! A TFTCommunicator device forms the bridge between the TFT class and the physical screen. */
class TFTCommunicator
{
    public:

        /*! \name Single functions
         *  Functions to read and write single commands or items of data
         */
        /**@{*/

        /*! Read an 8-bit command from the device */
        virtual uint8_t readCommand8() = 0;
        /*! Read a 16-bit command from the device */
        virtual uint16_t readCommand16() = 0;
        /*! Read a 32-bit command from the device */
        virtual uint32_t readCommand32() = 0;
        /*! Write an 8-bit command to the device */
        virtual void writeCommand8(uint8_t command) = 0;
        /*! Write a 16-bit command to the device */
        virtual void writeCommand16(uint16_t command) = 0;
        /*! Write a 32-bit command to the device */
        virtual void writeCommand32(uint32_t command) = 0;

        /*! Read 8 bits of data from the device */
        virtual uint8_t readData8() = 0;
        /*! Read 16 bits of data from the device */
        virtual uint16_t readData16() = 0;
        /*! Read 32 bits of data from the device */
        virtual uint32_t readData32() = 0;
        /*! Write 8 bits of data to the device */
        virtual void writeData8(uint8_t data) = 0;
        /*! Write 16 bits of data to the device */
        virtual void writeData16(uint16_t data) = 0;
        /*! Write 32 bits of data to the device */
        virtual void writeData32(uint32_t data) = 0;

        /**@}*/

        /*! \name Streaming functions
         *  Functions to read and write streams of mixed data and commands
         */
        /**@{*/
    
        /*! Open a stream to the device endpoint */
        virtual void streamStart() = 0;
        /*! Close the currently open stream */
        virtual void streamEnd() = 0;
        /*! Send an 8-bit command through the stream */
        virtual void streamCommand8(uint8_t data) = 0;
        /*! Send a 16-bit command through the stream */
        virtual void streamCommand16(uint16_t data) = 0;
        /*! Send a 32-bit command through the stream */
        virtual void streamCommand32(uint32_t data) = 0;
        /*! Read an 8-bit command through the stream */
        virtual uint8_t streamCommand8() = 0;
        /*! Read a 16-bit command through the stream */
        virtual uint16_t streamCommand16() = 0;
        /*! Read a 32-bit command through the stream */
        virtual uint32_t streamCommand32() = 0;

        /*! Send 8-bits of data through the stream */
        virtual void streamData8(uint8_t data) = 0;
        /*! Send 16-bits of data through the stream */
        virtual void streamData16(uint16_t data) = 0;
        /*! Send 32-bits of data through the stream */
        virtual void streamData32(uint32_t data) = 0;
        /*! Read 8 bits of data through the stream */
        virtual uint8_t streamData8() = 0;
        /*! Read 16 bits of data through the stream */
        virtual uint16_t streamData16() = 0;
        /*! Read 32 bits of data through the stream */
        virtual uint32_t streamData32() = 0;
    
        /**@}*/

        /*! \name Block data functions
         *  Functions to write large blocks of data
         */
        /**@{*/

        /*! Transfer a block of 8-bit data to the device */
        virtual void blockData(uint8_t *data, uint32_t len) = 0;
        /*! Transfer a block of 16-bit data to the device */
        virtual void blockData(uint16_t *data, uint32_t len) = 0;
        /*! Transfer a block of 32-bit data to the device */
        virtual void blockData(uint32_t *data, uint32_t len) = 0;

        /**@}*/

        /*! \name Device control functions
         *  Functions to manage the device
         */
        /**@{*/

        /*! Initialize the communication device */
        virtual void initializeDevice() = 0;
        /*! Returns the real physical width of the data channel */
        virtual uint8_t nativeWidth() = 0;

        /**@}*/
};

#endif
