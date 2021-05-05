#ifndef __LP50XX_H
#define __LP50XX_H


/**
 * @brief Class to communicate with the LP5009 or LP5012
 */
class LP50XX 
{
    public:
        LP50XX(); // Constructor

        /**
         * Initialisation functions
         */
        void Begin(uint8_t i2c_address = 0x52); // 

    protected:

    private:
        uint8_t     _i2c_address = 0x52;
};

#endif