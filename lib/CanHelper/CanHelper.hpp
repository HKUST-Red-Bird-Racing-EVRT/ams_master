#ifndef CANHELPER_HPP
#define CANHELPER_HPP

#include "AmsState.hpp"

#include <stdint.h>

// ignore -Wpedantic warnings for mcp2515.h
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <mcp2515.h>
#pragma GCC diagnostic pop

//  MCP2515 Address
#define MCP2515_PANIC_ADDRESS 0x100
#define MCP2515_MASTER_ADDRESS 0x200
#define MCP2515_SLAVE_ADDRESS 0x300

#define NUM_SLAVE 10
#define NUM_SLAVE_FRAME 5

class CanHelper {
    public:
        CanHelper(MCP2515 &mcp2515_0_, MCP2515 &mcp2515_1_, AmsState &ams_state_);
        CanHelper() = delete; // Delete the default constructor to prevent its use
        void packSlaveData(can_frame &rx_frame);

    private:
        MCP2515 &mcp2515_0;
        MCP2515 &mcp2515_1;
        AmsState &ams_state;

};

#endif // CANHELPER_HPP