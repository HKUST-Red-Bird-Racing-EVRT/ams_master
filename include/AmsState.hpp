#ifndef AMSSTATE_HPP
#define AMSSTATE_HPP

#include <stdint.h>

// ignore -Wpedantic warnings for mcp2515.h
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <mcp2515.h>
#pragma GCC diagnostic pop

#define NUM_SLAVE 10
#define NUM_VCELL 14
#define NUM_NTC 5


struct AmsState
{
    bool cellbal_active = false;
    bool cellbal_odd = false;
    bool discharge_active = false;
    bool fault_active = false;
    uint16_t cell_voltages[NUM_SLAVE][NUM_VCELL];
    uint16_t ntc_temperatures[NUM_SLAVE][NUM_NTC];
    uint16_t cellbal_states[NUM_SLAVE];
    uint8_t fault_slave;
    uint8_t fault_flags;
    uint8_t command_flags;

};

/*
Command Flag Bits
Bit 0: discharge_state
Bit 1: cellbal_state
Bit 2 - 15: cellbal_flags for cell 0 - 13 (1 = balancing, 0 = not balancing)
*/

#define DISCHARGE_STATE_BIT         0x01
#define CELLBAL_STATE_BIT           0x02
#define CELLBAL_ODD_BIT             0x04
#define SEQUENCE_TOGGLE_BIT         0x08

//  Cell Balancing Flag Masks
#define CELLBAL_EVEN_MASK           0x1555 // 0001 0101 0101 0101
#define CELLBAL_ODD_MASK            0x4AAA // 0100 1010 1010 1010

//  Fault Flag Bits
#define OVERVOLTAGE_FAULT_BIT       0x01
#define UNDERVOLTAGE_FAULT_BIT      0x02
#define OVERTEMPERATURE_FAULT_BIT   0x04
#define UNDERTEMPERATURE_FAULT_BIT  0x08
#define I2C_TIMEOUT_FAULT_BIT       0x10
#define CAN_TIMEOUT_FAULT_BIT       0x20

#endif // AMSSTATE_HPP