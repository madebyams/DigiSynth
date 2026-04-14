#include "clock.hh"

#include <stdint.h>

#include "gpio.hh"
#include "usart.hh"
#include "i2c.hh"

static const char * const note_names[gpio::NUM_KEYS] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

static uint8_t debounce_cnt[gpio::NUM_KEYS];
static uint8_t key_active[gpio::NUM_KEYS];

int main()
{
    sys_clock clk;
    gpio  gpio_drv;
    usart usart_drv;
    i2c   i2c_drv;

    clk.init();
    gpio_drv.init();
    usart_drv.init();
    i2c_drv.init();

    usart_drv.puts("Keyboard Unit Ready\r\n");

    for (;;)
    {
        for (uint8_t i = 0; i < gpio::NUM_KEYS; i++)
        {
            if (gpio_drv.readKey(i))
            {
                if (debounce_cnt[i] < gpio::DEBOUNCE_COUNT)
                    debounce_cnt[i]++;

                if (debounce_cnt[i] == gpio::DEBOUNCE_COUNT && !key_active[i])
                {
                    key_active[i] = 1;

                    gpio_drv.sendTrigger();    /* 1. pulse PB4 → slave EXTI  */
                    i2c_drv.sendNote(i);       /* 2. send note index over I2C */

                    usart_drv.puts("Key: ");  /* 3. debug output             */
                    usart_drv.puts(note_names[i]);
                    usart_drv.puts("\r\n");
                }
            }
            else
            {
                debounce_cnt[i] = 0;
                key_active[i]   = 0;
            }
        }
    }
}
