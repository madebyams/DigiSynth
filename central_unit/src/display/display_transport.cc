//
// Created by Amsakan on 27.01.26.
//
#include <cerrno>
#include <cstring>
#include <sys/ioctl.h>

#include <fmt/base.h>

#include "../../include/display/display_transport.hh"
#include "display/display_registers.hh"

using registers = display_registers;

bool display_transport::init() {
    return this->i2c_.init();
}

bool display_transport::select() {
    return i2c_.select(ADDRESS);
}

bool display_transport::write_command(const uint8_t command) {
    uint8_t buffer[2] = {
        static_cast<uint8_t>(registers::COMMAND),
        command
    };

    this->select();
    return this->i2c_.transmit(buffer, 2);
}

bool display_transport::write_data(const uint8_t data) {
    uint8_t buffer[2] = {
        static_cast<uint8_t>(registers::DATA),
        data
    };

    this->select();
    return this->i2c_.transmit(buffer, 2);
}

bool display_transport::write_multi_data(uint8_t* data, uint32_t count) {
    uint8_t buffer[count + 1];

    buffer[0] = static_cast<uint8_t>(registers::DATA);
    std::memcpy(&buffer[1], data, count);

    this->select();
    return this->i2c_.transmit(buffer, count + 1);
}

bool display_transport::terminate() {
    return this->i2c_.terminate();
}
