#include <chrono>
#include <thread>

#include <fmt/base.h>

#include "display/display.hh"
#include "display/fonts/fonts.hh"

int main() {
    char buffer[128] = {};
    i2c i2c;

    display display(i2c);
    display.init();
    display.puts("Hello world!", &Fonts::Font_7x10, display::White);

    /*
    while (true) {
        i2c.select(0x4d);
        i2c.receive(reinterpret_cast<uint8_t*>(buffer), 128);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        fmt::print("I2C msg: {}", buffer);
    }*/

    display.terminate();
    return 0;
}