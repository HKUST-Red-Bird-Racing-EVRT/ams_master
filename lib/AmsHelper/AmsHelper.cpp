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

void AmsHelper::updateBatterySOC(int8_t hall_lo, int8_t hall_hi) {
    ams.coulomb_count = hall_hi - hall_lo; // Calculate the coulomb count based on hall sensor readings
    // TODO: Implement a more accurate SOC calculation based on coulomb count and battery capacity
}

void AmsHelper::updateAIR(AIRState new_state) {
    ams.air_state = new_state;
    switch (ams.air_state) {
        case AIRState::INIT:
            // Handle INIT state
            digitalWrite(PIN_AIR_NEG, HIGH);
            digitalWrite(PIN_AIR_POS, LOW);
            digitalWrite(PIN_AIR_PRE, HIGH);
            break;
        case AIRState::ACTIVE:
            // Handle ACTIVE state
            digitalWrite(PIN_AIR_NEG, HIGH);
            digitalWrite(PIN_AIR_POS, HIGH);
            digitalWrite(PIN_AIR_PRE, LOW);
            break;
        case AIRState::SHUTDOWN:
            // Handle SHUTDOWN state
            digitalWrite(PIN_AIR_NEG, LOW);
            digitalWrite(PIN_AIR_POS, LOW);
            digitalWrite(PIN_AIR_PRE, LOW);
            break;
        default:
            // Handle unknown state
            break;
    }
}