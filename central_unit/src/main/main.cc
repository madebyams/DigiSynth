#include "display/display.hh"
#include "display/fonts/fonts.hh"

int main() {
    i2c i2c;

    display display(i2c);
    display.init();
    display.puts("Hello world!", &Fonts::Font_7x10, display::White);
    return 0;
}