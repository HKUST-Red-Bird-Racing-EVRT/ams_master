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

  pinMode(CAN0_CS, OUTPUT);
  pinMode(CAN1_CS, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (can_slave.readMessage(&rx_slave_frame) == MCP2515::ERROR_OK)
  {
    can_helper.packSlaveData(rx_slave_frame);
  }
}
