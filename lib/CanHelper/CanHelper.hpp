#ifndef CANHELPER_HPP
#define CANHELPER_HPP

#include "AmsState.hpp"
#include "BoardConfig.h"

#include <stdint.h>
#include <Arduino.h>

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
#define NUM_SLAVE_FRAME 6

#define CAN_TIMEOUT_MAX 500

class CanHelper {
    public:
        CanHelper(MCP2515 &can_slave_, MCP2515 &mcp2515_1_, AmsState &ams_);
        CanHelper() = delete; // Delete the default constructor to prevent its use
        void packingMaskCellBalState(uint16_t &flag);
        void drainCanBuffer();
        void packSlaveData(can_frame &rx_frame);
        bool isCommunicationTimeoutOld();
        bool isDelayedFrame(can_frame &frame);
        void sendSlaveData(uint8_t index);

    private:
        MCP2515 &can_slave;
        MCP2515 &mcp2515_1;
        AmsState &ams;

};

//  Master Command Byte bits
#define MASTERCMD_DISCHARGE_STATE_BIT   0x01
#define MASTERCMD_CELLBAL_STATE_BIT     0x02
#define MASTERCMD_CELLBAL_ODD_BIT       0x04
#define MASTERCMD_SEQTOGGLE_BIT         0x08

#endif // CANHELPER_HPP