#include "adsr.hh"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_adc.h"

bool ADSR::init() {
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ENABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = ENABLE;
    hadc1.Init.NbrOfDiscConversion = 1;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 4;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        return false;
    }

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return false;
    }

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = 2;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return false;
    }

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = 3;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return false;
    }

    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    */
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = 4;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        return false;
    }
    
    return true;
}

void ADSR::read_value() {
    for(int i = 0; i < ADC_CHANNELS; i++) {
        HAL_ADC_Start(&this->hadc1);
        HAL_ADC_PollForConversion(&this->hadc1, ADC_TIMEOUT);
        this->values[i] = HAL_ADC_GetValue(&this->hadc1);
    }

    HAL_ADC_Stop(&this->hadc1);

    this->envelope = {
        .attack = this->values[0],
        .decay = this->values[1],
        .sustain = this->values[2],
        .release = this->values[3]
    };
}

ADSR::Envelope ADSR::get_envelope() {
    return this->envelope;
}