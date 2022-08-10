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

/* Device address */
#define AXP2101_ADDR            0x34
#define AXP2101_ADDR_READ       0x69
#define AXP2101_ADDR_WRITE      0x68
/* Internal REG address */
#define AXP2101_REG_COM_CONFIG  0x10
#define AXP2101_REG_DCDC_ONOFF  0x80
#define AXP2101_REG_DCDC1_VSET  0x82
#define AXP2101_REG_DCDC2_VSET  0x83
#define AXP2101_REG_LDO_ONOFF   0x90
#define AXP2101_REG_ALDO1_VSET  0x92
#define AXP2101_REG_ALDO2_VSET  0x93
#define AXP2101_REG_ALDO3_VSET  0x94
#define AXP2101_REG_ALDO4_VSET  0x95
#define AXP2101_REG_BLDO1_VSET  0x96
#define AXP2101_REG_BLDO2_VSET  0x97


/* AXP2101 class */
class AXP2101 : public I2C_PORT {
    private:
        uint16_t _getMin(uint16_t a, uint16_t b);
        uint16_t _getMax(uint16_t a, uint16_t b);
        uint16_t _getMid(uint16_t input, uint16_t min, uint16_t max);
    public:
        /* Type defines */
        typedef enum {
            DCDC1 = 0,
            DCDC2,
            DCDC3,
            DCDC4,
            ALDO1,
            ALDO2,
            ALDO3,
            ALDO4,
            BLDO1,
            BLDO2,
        } OUTPUT_CHANNEL;

        /* Functions */
        bool begin(TwoWire* wire = &Wire);
        void powerOff();
        void setOutputState(OUTPUT_CHANNEL channel, bool state);
        void setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage);
};


#endif