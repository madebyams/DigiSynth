//
// Created by Amsakan on 02.02.26.
//

#ifndef CENTRAL_UNIT_DISPLAY_TRANSPORT_HH
#define CENTRAL_UNIT_DISPLAY_TRANSPORT_HH
#include <cstdint>

#include "i2c.hh"

constexpr uint32_t ADDRESS = 0x3c;

class display_transport {
    i2c& i2c_;
    bool select();
public:
    explicit display_transport(i2c& i2c) : i2c_(i2c) {};
    bool init();
    bool write_command(const uint8_t command);
    bool write_data(uint8_t data);
    bool write_multi_data(uint8_t* data, uint32_t count);
    bool terminate();
};
#endif //CENTRAL_UNIT_DISPLAY_TRANSPORT_HH