//
// Created by Amsakan on 27.01.26.
//
#include <cerrno>
#include <cstring>
#include <sys/fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <fmt/base.h>

#include "../../include/display/display_i2c.hh"
#include "SSD1306/SSD1306_Registers.hh"

using namespace SSD1306;

bool I2C::init() {
    this->handle = open("/dev/i2c-1", O_RDWR);

    if (this->handle < 0) {
        fmt::print(stderr, "Error opening I2C interface! ({})\n", strerror(errno));
        return false;
    }

    if (ioctl(this->handle, I2C_SLAVE, this->address) < 0) {
        fmt::print(stderr, "Error initializing I2C interface! {}\n", strerror(errno));
        return false;
    }

    return true;
}

void I2C::write_command(const uint8_t command) {
    ssize_t err;
    uint8_t buffer[2] = {
        0x00,
        command
    };

    err = write(this->handle, buffer, 2);
    if (err < 0) {
        fmt::print(stderr, "Error writing data ({})\n", strerror(errno));
        this->terminate();
    }
}

void I2C::write_multi_data(uint8_t* data, uint32_t count) {
    ssize_t err;
    uint8_t buffer[count + 1];

    buffer[0] = static_cast<uint8_t>(Registers::DATA);
    std::memcpy(&buffer[1], data, count);

    err = write(this->handle, buffer, count + 1);
    if (err < 0) {
        fmt::print(stderr, "Error writing data ({})\n", strerror(errno));;
        this->terminate();
    }
}

bool I2C::terminate() {
    if (int err = close(this->handle); err < 0) {
        return false;
    }

    return true;
}
