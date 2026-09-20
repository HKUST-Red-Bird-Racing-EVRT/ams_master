#ifndef AMSHELPER_HPP
#define AMSHELPER_HPP

#include "AmsState.hpp"
#include "BoardConfig.h"
#include <Arduino.h>

#define TIME_SETUP 1000
#define DEFAULT_VOLTAGE_MAX 4250
#define DEFAULT_VOLTAGE_MIN 3700

class AmsHelper {
    public:
        AmsHelper(AmsState &ams_);
        AmsHelper() = delete; // Delete the default constructor to prevent its use
        void resetCellBal();
        void updateMaxMinCellVoltages();
        void updateMaxMinTemperatures();
        void updateBatterySOC(int8_t hall_lo, int8_t hall_hi);
        void updateAIR(AIRState new_state);

    private:
        AmsState &ams;

};

#endif // AMSHELPER_HPP