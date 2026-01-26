#ifndef ADSR_HH
#define ADSR_HH

#include "stm32f4xx_hal.h"
#include <cstdint>

constexpr uint32_t ADC_TIMEOUT = 1000;
constexpr uint8_t ADC_CHANNELS = 4;

class ADSR {
public:
    struct Envelope {
        uint16_t attack;
        uint16_t decay;
        uint16_t sustain;
        uint16_t release;
    };

    bool init();
    void read_value();
    Envelope get_envelope();
private:
    ADC_HandleTypeDef hadc1;
    uint16_t values[ADC_CHANNELS];
    Envelope envelope;
};

#endif