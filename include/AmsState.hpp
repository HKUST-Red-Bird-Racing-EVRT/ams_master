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
    bool is_cellbal_active = false;
    bool is_cellbal_even = false;
    const uint16_t cell_voltages_max = 4250;
    uint16_t cell_voltages_min = 3700;
    uint16_t cell_voltages[NUM_SLAVE][NUM_VCELL];
    uint16_t ntc_temperatures[NUM_SLAVE][NUM_NTC];
    uint16_t cellbal_states[NUM_SLAVE];
    

};

// Your AmsState class definition here

#endif // AMSSTATE_HPP