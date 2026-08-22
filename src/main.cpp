#include <Arduino.h>

// ignore -Wpedantic warnings for mcp2515.h
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <mcp2515.h>
#pragma GCC diagnostic pop

#include "BoardConfig.h"
#include "AmsState.hpp"
#include "CanHelper.hpp"

MCP2515 mcp2515_0(CAN0_CS);
MCP2515 mcp2515_1(CAN1_CS);
can_frame rx_frame_0;

AmsState ams_state;

void setup() {
  // put your setup code here, to run once:

  pinMode(CAN0_CS, OUTPUT);
  pinMode(CAN1_CS, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  

}

