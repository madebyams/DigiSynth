#pragma once

#include <stdint.h>

/*
 * Pin assignment:
 *   PA0–PA7  : keys 0–7  (C–G)   — input pull-up
 *   PB0–PB3  : keys 8–11 (G#–B)  — input pull-up
 *   PB4      : EXTI trigger out   — push-pull
 *   PB6      : I2C1 SCL           — AF open-drain
 *   PB7      : I2C1 SDA           — AF open-drain
 *   PA9      : USART1 TX          — AF push-pull
 */
class gpio {
public:
    static constexpr uint8_t TRIGGER_PIN    = 4;
    static constexpr uint8_t NUM_KEYS       = 12;
    static constexpr uint8_t DEBOUNCE_COUNT = 50;

    void init();

    /* Returns 1 if key at index idx is currently pressed (active-low) */
    int  readKey(uint8_t idx);

    /* Pulses PB4 high for ~10 µs to trigger EXTI on slave */
    void sendTrigger();
};
