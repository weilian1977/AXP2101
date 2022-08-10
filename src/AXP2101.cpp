#include "AXP2101.h"



/**
 * @brief Return min input
 * 
 * @param a 
 * @param b 
 * @return uint16_t 
 */
inline uint16_t AXP2101::_getMin(uint16_t a, uint16_t b) {
    return ((a)<(b)?(a):(b));
}

/**
 * @brief Return max input
 * 
 * @param a 
 * @param b 
 * @return uint16_t 
 */
inline uint16_t AXP2101::_getMax(uint16_t a, uint16_t b) {
    return ((a)>(b)?(a):(b));
}

/**
 * @brief Return limited input
 * 
 * @param input 
 * @param min 
 * @param max 
 * @return uint16_t 
 */
uint16_t AXP2101::_getMid(uint16_t input, uint16_t min, uint16_t max) {
    return _getMax(_getMin(input, max), min);
}

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
    _I2C_write1Byte(AXP2101_REG_COM_CONFIG, (_I2C_read8Bit(AXP2101_REG_COM_CONFIG) | 0B00000001));
}


/**
 * @brief Set output channel ON/OFF
 * 
 * @param channel 
 * @param state true: ON / false: OFF
 */
void AXP2101::setOutputState(OUTPUT_CHANNEL channel, bool state) {
    /* DCCDs */
    if (channel < ALDO1) {
        uint8_t buff = _I2C_read8Bit(AXP2101_REG_DCDC_ONOFF);
        buff = state ? ( buff | (1U << channel) ) : ( buff & ~(1U << channel) );
        _I2C_write1Byte(AXP2101_REG_DCDC_ONOFF, buff);
    }
    /* LDOs */
    else {
        uint8_t buff = _I2C_read8Bit(AXP2101_REG_LDO_ONOFF);
        buff = state ? ( buff | (1U << (channel - ALDO1)) ) : ( buff & ~(1U << (channel - ALDO1)) );
        _I2C_write1Byte(AXP2101_REG_LDO_ONOFF, buff);
    }
}


/**
 * @brief Set output channel's voltage
 * 
 * @param channel 
 * @param voltage LDO: 500~3500 mA
 */
void AXP2101::setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage) {
    /* DCDCs */
    if (channel < ALDO1) {

    }
    /* LDOs */  
    else {
        /* Map voltage to 0~30 */
        voltage = (_getMid(voltage, 500, 3500) / 100) - 5;
        /* Get REG address */
        uint8_t addr = channel + 142;
        uint8_t buff = _I2C_read8Bit(addr);
        buff = (buff & 0B11100000) | (voltage & 0B00011111);
        _I2C_write1Byte(addr, buff);
    }
}

