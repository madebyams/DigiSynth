#include "Display.hh"

Display display;

int main(void) {
    display.init();
    display.puts("Hello world!", &Fonts::Font_7x10, Display::White);
    display.terminate();
    return 0;
}