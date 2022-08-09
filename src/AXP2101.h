/**
 * @file AXP2101.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2022-08-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _AXP2101_H_
#define _AXP2101_H_

/* Includes */
#include "Arduino.h"
#include "Wire.h"
#include "i2c_port/i2c_port.h"

/* Defines */
#define AXP2101_ADDR         0x34
#define AXP2101_ADDR_READ    0x69
#define AXP2101_ADDR_WRITE   0x68

/* AXP2101 class */
class AXP2101 : public I2C_PORT {
    private:
    public:
    bool begin(TwoWire* wire = &Wire);
    void powerOff();
};


#endif