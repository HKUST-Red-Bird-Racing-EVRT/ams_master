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
    uint8_t fault_flags;
    

};

// Your AmsState class definition here

#endif // AMSSTATE_HPP