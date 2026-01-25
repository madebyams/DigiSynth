#ifndef DAC_HH
#define DAC_HH

#include "stm32f4xx_hal.h"

constexpr double PI = 3.14159265358979323846;
constexpr uint32_t SAMPLE_RATE = 44100u;
constexpr uint32_t CHANNELS = 2u;
constexpr float LATENCY_S = 0.01f; // 10 ms
constexpr uint32_t FRAMES = static_cast<uint32_t>(SAMPLE_RATE * LATENCY_S + 0.5f);
constexpr uint32_t BUFFER_SIZE = FRAMES * CHANNELS; // number of 16-bit samples

class DAC {
    I2S_HandleTypeDef hi2s2;
    uint16_t buffer[BUFFER_SIZE] = {};
public:
    bool init();
    bool play_sine(const float frequency);
};

#endif