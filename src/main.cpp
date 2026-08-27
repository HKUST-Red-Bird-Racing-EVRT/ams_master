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

MCP2515 can_slave(CAN0_CS);
MCP2515 mcp2515_1(CAN1_CS);
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

  pinMode(CAN0_CS, OUTPUT);
  pinMode(CAN1_CS, OUTPUT);

  delay(1000); // Wait for 1 second before starting the loop
}

void loop()
{
  // put your main code here, to run repeatedly:

  /*
  Later Implementation:
  - Master send command byte to slave
  - Before receiving data from slave, communicate with vcu first
  */

  if (can_slave.readMessage(&rx_slave_frame) == MCP2515::ERROR_OK)
  {
    can_helper.packSlaveData(rx_slave_frame);
  }

  if (millis() >= TIME_SETUP)
  {
    
    if (!can_helper.isCommunicationTimeout())
    {
      ams_helper.updateMinCellVoltages();
    }
    
  }

}
