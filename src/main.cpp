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

MCP2515 can_slave(PIN_CAN0_CS);
MCP2515 mcp2515_1(PIN_CAN1_CS);
can_frame rx_slave_frame;

AmsState ams;
AmsHelper ams_helper(ams);
CanHelper can_helper(can_slave, mcp2515_1, ams);

void setup()
{
  // put your setup code here, to run once:

  can_slave.reset();
	can_slave.setBitrate(CAN_500KBPS, MCP_20MHZ);
	can_slave.setNormalMode();

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

  if (can_slave.readMessage(&rx_slave_frame) == MCP2515::ERROR_OK)
  {
    can_helper.packSlaveData(rx_slave_frame);
  }

  if (millis() >= TIME_SETUP)
  {
    
    if (!can_helper.isCommunicationTimeoutOld())
    {
      ams_helper.updateMinCellVoltages();
    }
    
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
