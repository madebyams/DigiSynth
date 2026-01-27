//
// Created by Amsakan on 27.01.26.
//

#ifndef CENTRAL_UNIT_SSD1306_I2C_HH
#define CENTRAL_UNIT_SSD1306_I2C_HH

#include <cstdint>

namespace SSD1306 {
    class I2C {
        uint8_t address;
        int handle = 0;
    public:
        explicit I2C(uint8_t address) : address(address) {};
        bool init();
        void write_command(uint8_t command);
        void write_multi_data(uint8_t* data, uint32_t count);
        bool terminate();
    };
}
#endif //CENTRAL_UNIT_SSD1306_I2C_HH