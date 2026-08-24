#ifndef AMSHELPER_HPP
#define AMSHELPER_HPP

#include <stdint.h>
#include "AmsState.hpp"

#define TIME_SETUP 1000
#define DEFAULT_VOLTAGE_MIN 3700

class AmsHelper {
    public:
        const uint16_t VOLTAGE_MAX = 4250;
        uint16_t voltage_min = DEFAULT_VOLTAGE_MIN;

        AmsHelper(AmsState &ams_);
        AmsHelper() = delete; // Delete the default constructor to prevent its use
        void resetCellBal();
        void updateMinCellVoltages();

    private:
        AmsState &ams;

};

#endif // AMSHELPER_HPP