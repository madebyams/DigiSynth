#include "dac.hh"
#include "main.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2s.h"
#include <cmath>

bool DAC::init() {
    hi2s2.Instance = SPI2;
    hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
    hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B;
    hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_44K;
    hi2s2.Init.CPOL = I2S_CPOL_LOW;
    hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
    hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
    if (HAL_I2S_Init(&hi2s2) != HAL_OK) {
        return false;
    }

    return true;
}

bool DAC::play_sine(const float frequency) {
    const float amplitude = static_cast<float>(INT16_MAX) * 0.5f; // reduce amplitude to avoid clipping
    // fill buffer: interleaved stereo (L,R) with same sample
    for (uint32_t frame = 0; frame < FRAMES; ++frame) {
        float t = static_cast<float>(frame) / static_cast<float>(SAMPLE_RATE);
        float s = amplitude * std::sinf(2.0f * static_cast<float>(PI) * frequency * t);
        int16_t sample = static_cast<int16_t>(s);
        uint16_t word = static_cast<uint16_t>(static_cast<int16_t>(sample));
        // interleaved channels
        buffer[frame * CHANNELS + 0] = word;
        buffer[frame * CHANNELS + 1] = word;
    }

    // Start DMA once. DMA must be configured to circular mode for continuous play.
    if (HAL_I2S_Transmit_DMA(&this->hi2s2, const_cast<uint16_t*>(this->buffer), BUFFER_SIZE) != HAL_OK) {
        return false;
    }

    // Do not call HAL_I2S_Transmit_DMA repeatedly. Let DMA run (circular) or handle half/full callbacks.
    return true;
}