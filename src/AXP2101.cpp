#include "AXP2101.h"


/**
 * @brief Init AXP2101
 * 
 * @param wire I2C wire pointer
 * @return true Init failed
 * @return false Init successful
 */
bool AXP2101::begin(TwoWire* wire) {
    _I2C_init(wire, AXP2101_ADDR);
    return _I2C_checkDevAvl();
}


/**
 * @brief Turn the power off
 * 
 */
void AXP2101::powerOff() {
    _I2C_write1Byte(0x10, (_I2C_read8Bit(0x10) | 0B00000001));
}

