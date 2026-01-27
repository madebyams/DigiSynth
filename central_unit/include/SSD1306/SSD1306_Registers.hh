//
// Created by Amsakan on 27.01.26.
//

#ifndef CENTRAL_UNIT_SSD1306_REGISTERS_HH
#define CENTRAL_UNIT_SSD1306_REGISTERS_HH
namespace SSD1306 {
    enum class Registers : uint8_t {
        DATA = 0x40,
        COMMAND = 0x00
    };
};
#endif //CENTRAL_UNIT_SSD1306_REGISTERS_HH