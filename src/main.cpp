#include <Arduino.h>

// ignore -Wpedantic warnings for mcp2515.h
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <mcp2515.h>
#pragma GCC diagnostic pop

#include "BoardConfig.h"
#include "AmsState.hpp"
#include "AmsHelper.hpp"
#include "CanHelper.hpp"

MCP2515 can_internal(PIN_CAN0_CS);
MCP2515 mcp2515_1(PIN_CAN1_CS);
can_frame rx_slave_frame;

AmsState ams;
AmsHelper ams_helper(ams);
CanHelper can_helper(can_internal, mcp2515_1, ams, ams_helper);

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

  delay(1000); // Wait for 1 second before starting the loop
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

  if (!can_helper.isCommunicationTimeoutOld())
  {
    ams_helper.updateMaxMinCellVoltages();
  }

  for (uint8_t slave_index = 0; slave_index < NUM_SLAVE; ++slave_index)
  {
    // if frame dropped, keep looping for 3-4 times to request the slave data again, and drain the buffer
    uint8_t retry_count = 0;
    while (retry_count < 4)
    {
      can_helper.requestSlaveData(slave_index);
      can_helper.drainCanBuffer();
      if (can_helper.isCommunicationTimeoutOld())
      {
        retry_count++;
      }
      else
      {
        break;
      }
    }
  }
}
