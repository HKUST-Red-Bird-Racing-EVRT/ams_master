#include "CanHelper.hpp"

CanHelper::CanHelper(MCP2515 &mcp2515_0_, MCP2515 &mcp2515_1_, AmsState &ams_state_)
    : mcp2515_0(mcp2515_0_), mcp2515_1(mcp2515_1_), ams_state(ams_state_)
{
    // Constructor implementation
}

void CanHelper::packSlaveData(can_frame &rx_frame)
{
    // Implementation of the packSlaveData function
    // This function will handle the packing of slave data into CAN frames

    uint8_t slave_index = (rx_frame.can_id - MCP2515_SLAVE_ADDRESS) / NUM_SLAVE_FRAME; // Extract the slave index from the CAN ID
    uint8_t slave_frame = (rx_frame.can_id - MCP2515_SLAVE_ADDRESS) % NUM_SLAVE_FRAME; // Extract the slave frame index from the CAN ID

    switch (slave_frame)
    {
        case 0:
        ams_state.cellbal_states[slave_index] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming cellbal_states is a 16-bit value
        ams_state.cell_voltages[slave_index][0] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][1] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][2] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
        break;

        case 1:
        ams_state.cell_voltages[slave_index][3] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][4] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][5] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][6] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
        break;

        case 2:
        ams_state.cell_voltages[slave_index][7] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][8] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][9] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][10] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming cell_voltages is a 16-bit value
        break;

        case 3:
        ams_state.cell_voltages[slave_index][11] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][12] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.cell_voltages[slave_index][13] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming cell_voltages is a 16-bit value
        ams_state.ntc_temperatures[slave_index][0] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming ntc_temperatures is a 16-bit value
        break;

        case 4:
        ams_state.ntc_temperatures[slave_index][1] = rx_frame.data[0] | (rx_frame.data[1] << 8); // Assuming ntc_temperatures is a 16-bit value
        ams_state.ntc_temperatures[slave_index][2] = rx_frame.data[2] | (rx_frame.data[3] << 8); // Assuming ntc_temperatures is a 16-bit value
        ams_state.ntc_temperatures[slave_index][3] = rx_frame.data[4] | (rx_frame.data[5] << 8); // Assuming ntc_temperatures is a 16-bit value
        ams_state.ntc_temperatures[slave_index][4] = rx_frame.data[6] | (rx_frame.data[7] << 8); // Assuming ntc_temperatures is a 16-bit value
        break;

        default:
        break;
    }
}