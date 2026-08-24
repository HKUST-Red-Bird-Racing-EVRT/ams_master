#include "CanHelper.hpp"

CanHelper::CanHelper(MCP2515 &can_slave_, MCP2515 &mcp2515_1_, AmsState &ams_)
    : can_slave(can_slave_), mcp2515_1(mcp2515_1_), ams(ams_)
{
    // Constructor implementation
}

void CanHelper::packSlaveData(can_frame &rx_frame)
{
    // Implementation of the packSlaveData function
    // This function will handle the packing of slave data into CAN frames

    if (rx_frame.can_id >= MCP2515_SLAVE_ADDRESS)
    {

        uint8_t buffer_index = rx_frame.can_id - MCP2515_SLAVE_ADDRESS; // Calculate the buffer index based on the CAN ID
        uint8_t slave_index = buffer_index / NUM_SLAVE_FRAME;           // Extract the slave index from the CAN ID
        uint8_t slave_frame = buffer_index % NUM_SLAVE_FRAME;           // Extract the slave frame index from the CAN ID

        rx_slave_buffer[buffer_index].frame = rx_frame;     // Store the received frame in the buffer
        rx_slave_buffer[buffer_index].timestamp = millis(); // Store the timestamp of when the frame was received

        switch (slave_frame)
        {
        case 0:
            ams.cellbal_states[slave_index] = rx_frame.data[0] | (rx_frame.data[1] << 8);   // Assuming cellbal_states is a 16-bit value
            ams.cell_voltages[slave_index][0] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][1] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][2] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
            break;

        case 1:
            ams.cell_voltages[slave_index][3] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][4] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][5] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][6] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
            break;

        case 2:
            ams.cell_voltages[slave_index][7] = rx_frame.data[0] | (rx_frame.data[1] << 8);  // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][8] = rx_frame.data[2] | (rx_frame.data[3] << 8);  // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][9] = rx_frame.data[4] | (rx_frame.data[5] << 8);  // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][10] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
            break;

        case 3:
            ams.cell_voltages[slave_index][11] = rx_frame.data[0] | (rx_frame.data[1] << 8);   // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][12] = rx_frame.data[2] | (rx_frame.data[3] << 8);   // Assuming cell_voltages is a 16-bit value
            ams.cell_voltages[slave_index][13] = rx_frame.data[4] | (rx_frame.data[5] << 8);   // Assuming cell_voltages is a 16-bit value
            ams.ntc_temperatures[slave_index][0] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming ntc_temperatures is a 16-bit value
            break;

        case 4:
            ams.ntc_temperatures[slave_index][1] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming ntc_temperatures is a 16-bit value
            ams.ntc_temperatures[slave_index][2] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming ntc_temperatures is a 16-bit value
            ams.ntc_temperatures[slave_index][3] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming ntc_temperatures is a 16-bit value
            ams.ntc_temperatures[slave_index][4] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming ntc_temperatures is a 16-bit value
            break;

        default:
            break;
        }
    }

    else if (rx_frame.can_id < MCP2515_MASTER_ADDRESS && rx_frame.can_id >= MCP2515_PANIC_ADDRESS)
    {
        ams.fault_active = true;
    }
}

bool CanHelper::isCommunicationTimeout()
{
    uint32_t current_time = millis();
    for (uint8_t i = 0; i < NUM_SLAVE * NUM_SLAVE_FRAME; ++i)
    {
        if (current_time - rx_slave_buffer[i].timestamp > COMMUNICATION_TIMEOUT_MAX)
        {
            return true; // Communication timeout occurred
        }
    }
    return false; // No communication timeout
}