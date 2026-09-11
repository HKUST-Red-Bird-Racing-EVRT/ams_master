#include "AmsHelper.hpp"

AmsHelper::AmsHelper(AmsState &ams_)
    : ams(ams_)
{
    // Constructor implementation
}

void AmsHelper::resetCellBal() {
    ams.cellbal_active = false;
    ams.cellbal_odd = false;
    ams.voltage_min = DEFAULT_VOLTAGE_MIN;
    ams.voltage_max = DEFAULT_VOLTAGE_MAX;
}

void AmsHelper::updateMaxMinCellVoltages() {
    uint16_t voltage_min = 0;
    uint16_t voltage_max = 0;
    for (uint8_t slave_index = 0; slave_index < NUM_SLAVE; ++slave_index) {

        for (uint8_t cell_index = 1; cell_index < NUM_VCELL; ++cell_index) {
            if (ams.cell_voltages[slave_index][cell_index] < voltage_min) {
                voltage_min = ams.cell_voltages[slave_index][cell_index];
            }
            if (ams.cell_voltages[slave_index][cell_index] > voltage_max) {
                voltage_max = ams.cell_voltages[slave_index][cell_index];
            }
        }
    }
    ams.voltage_min = voltage_min;
    ams.voltage_max = voltage_max;
}

void AmsHelper::updateMaxMinTemperatures() {
    uint16_t temperature_min = 0;
    uint16_t temperature_max = 0;
    for (uint8_t slave_index = 0; slave_index < NUM_SLAVE; ++slave_index) {

        for (uint8_t ntc_index = 1; ntc_index < NUM_NTC; ++ntc_index) {
            if (ams.ntc_temperatures[slave_index][ntc_index] < temperature_min) {
                temperature_min = ams.ntc_temperatures[slave_index][ntc_index];
            }
            if (ams.ntc_temperatures[slave_index][ntc_index] > temperature_max) {
                temperature_max = ams.ntc_temperatures[slave_index][ntc_index];
            }
        }
    }
    ams.temperature_min = temperature_min;
    ams.temperature_max = temperature_max;
}