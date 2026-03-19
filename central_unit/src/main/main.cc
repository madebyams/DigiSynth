#include <chrono>
#include <thread>

#include <pigpio.h>
#include <pigpiod_if.h>
#include <fmt/base.h>

#include "display/display.hh"
#include "display/Fonts/fonts.hh"

#define KEYBOARD_INTERRUPT_PIN 4

void interrupt_handler(int gpio, int level, uint32_t tick) {
    fmt::print("Signal received!");
}

int main() {
    gpioCfgSetInternals(PI_CFG_NOSIGHANDLER);

    if (int err = gpioInitialise(); err < 0) {
        fmt::print(stderr, "Failed to initialize pigpio ({})!\n", pigpio_error(err));
        return 1;
    }
    gpioSetMode(KEYBOARD_INTERRUPT_PIN, PI_INPUT);
    gpioSetPullUpDown(KEYBOARD_INTERRUPT_PIN, PI_PUD_UP);
    gpioSetAlertFunc(KEYBOARD_INTERRUPT_PIN, interrupt_handler);

    char buffer[128] = {};
    i2c i2c;

    display display(i2c);
    display.init();
    display.puts("Hello world!", &Fonts::Font_7x10, display::White);


    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    display.terminate();
    gpioTerminate();
    return 0;
}