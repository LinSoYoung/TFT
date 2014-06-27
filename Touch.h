/*
 * Generic touch screen interface for TFT devices
 */


#ifndef _TOUCH_H
#define _TOUCH_H

#include <TFT.h>

class Touch {
    public:
        /*! Create a new touch screen object
         *  ================================
         *  This takes a pointer to a communication device, and the width and height of the touch screen.
         */
        Touch(TFTCommunicator *comm, uint16_t w, uint16_t h) : _comm(comm), _width(w), _height(h) {}
        /*! Create a new touch screen object
         *  ================================
         *  This takes a reference to a communication device, and the width and height of the touch screen.
         */
        Touch(TFTCommunicator &comm, uint16_t w, uint16_t h) : _comm(&comm), _width(w), _height(h) {}
        /*! Create a new touch screen object
         *  ================================
         *  This creates a new controller-less touch device.
         */
        Touch(uint16_t w, uint16_t h) : _width(w), _height(h) {}
        /*! Initialize the device
         *  =====================
         *  This configures and enables the touch screen device. It should be called before any other touch screen
         *  functions.
         */
        virtual void initializeDevice() = 0;
        /*! Get X coordinate
         *  ================
         *  This returns the X coordinate of the current touch position.
         */
        virtual uint16_t x() = 0;
        /*! Get Y coordinate
         *  ================
         *  This returns the Y coordinate of the current touch position.
         */
        virtual uint16_t y() = 0;
        /*! Get pressed status
         *  ==================
         *  Returns true if the touch screen is pressed, false otherwise.
         */
        virtual boolean isPressed() = 0;
        /*! Calculate the touch pressure
         *  ============================
         *  For touch screens that can calculate how hard you are pressing them, this returns the pressure value.  For others it returns 0.
         *
         *  Example:
         *
         *      int pressure = ts.pressure();
         */
        virtual uint16_t pressure() { return 0; }
        /*! Set rotation
         *  ============
         *  This sets the screen orientation of the touch screen.  It should be set to the same as the
         *  rotation used for the screen.
         */
        virtual void setRotation(uint8_t r);

        /*! Sample the touch screen
         *  =======================
         *  This performs a sampling of the touch screen to get the current coordinates and touch status.
         *  It should be called regularly to update the current touch screen data.
         */
        virtual void sample() = 0;

    protected:
        /*! The communication device used to communicate with the touch screen controller (if any) */
        TFTCommunicator *_comm;  
        /*! The width of the toush screen in pixels */
        uint16_t _width;  
        /*! The height of the touch screen in pixels */
        uint16_t _height; 
};

#endif
