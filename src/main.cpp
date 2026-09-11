#include <Arduino.h>

// ignore -Wpedantic warnings for mcp2515.h
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <mcp2515.h>
#pragma GCC diagnostic pop

#include "BoardConfig.h"
#include "AmsState.hpp"
#include "AmsHelper.hpp"
#include "CanInternalHelper.hpp"

MCP2515 can_internal(PIN_CAN0_CS);
MCP2515 mcp2515_1(PIN_CAN1_CS);
can_frame rx_slave_frame;

AmsState ams;
AmsHelper ams_helper(ams);
CanInternalHelper can_internal_helper(can_internal, mcp2515_1, ams, ams_helper);

void setup()
{
  // put your setup code here, to run once:

  can_internal.reset();
  can_internal.setBitrate(CAN_500KBPS, MCP_20MHZ);
  can_internal.setConfigMode();

  // BUFFER 0 Setup: Covers 0x100 to 0x200
  // MASK0 = 0x700 (Checks top 3 bits: 0b111 0000 0000)
  can_internal.setFilterMask(MCP2515::MASK0, false, 0x700);

  // RXF0: Accepts 0x100 to 0x1FF (Top 3 bits match 0b001)
  can_internal.setFilter(MCP2515::RXF0, false, 0x100);

  // BUFFER 1 Setup: Covers 0x300 to 0x400
  // MASK1 = 0x700 (Checks top 3 bits: 0b111 0000 0000)
  can_internal.setFilterMask(MCP2515::MASK1, false, 0x700);

  // RXF2: Accepts 0x300 to 0x3FF (Top 3 bits match 0b011)
  can_internal.setFilter(MCP2515::RXF2, false, 0x300);

  can_internal.setNormalMode();

  pinMode(PIN_CAN0_CS, OUTPUT);
  pinMode(PIN_CAN1_CS, OUTPUT);
  pinMode(PIN_INT_0, INPUT);
  pinMode(PIN_INT_1, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  /*
  Later Implementation:
  - Master send command byte to slave
  - Before receiving data from slave, handle cell balancing odd/even states
  - Put recieved data into buffer, and update timestamp
  - If timeout, set fault flag and fault slave
  - If no timeout, communicate with vcu
  */

  for (uint8_t frame_index = 0; frame_index < NUM_SLAVE_FRAME; ++frame_index)
  {
    // if frame dropped, keep looping for 3-4 times to request the slave data again, and drain the buffer
    uint8_t retry_count = 0;
    while (retry_count < 4)
    {
      can_internal_helper.requestSlaveData(frame_index);
      can_internal_helper.drainCanBuffer();
      if (ams.fault_flags & CAN_TIMEOUT_FAULT_BIT)
      {
        retry_count++;
      }
      else
      {
        ams.fault_flags &= ~CAN_TIMEOUT_FAULT_BIT; // Clear the CAN timeout fault flag if no timeout occurred
        break;
      }
    }
  }

  if (ams.fault_flags)
  {
    // Handle fault condition, e.g., log the fault, notify the user, etc.
  }
  else
  {
    // Normal operation, e.g., send data to VCU, perform other tasks, etc.
    ams_helper.updateMaxMinCellVoltages();
    ams_helper.updateMaxMinTemperatures();
  }
}
