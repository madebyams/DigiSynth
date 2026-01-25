#include "dac.hh"
#include "main.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_i2s.h"
#include <cmath>

DMA_HandleTypeDef hdma_spi2_tx;

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

    hdma_spi2_tx.Instance = DMA1_Stream4;
    hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.Mode = DMA_CIRCULAR; // continuous playback
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK) {
        return false;
    }

    // Link DMA handle to I2S handle
    __HAL_LINKDMA(&hi2s2, hdmatx, hdma_spi2_tx);

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