//
// Created by Amsakan on 02.02.26.
//
#include <cerrno>
#include <cstring>
#include <sys/fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <fmt/base.h>

#include "i2c.hh"

bool i2c::init() {
    if (initialized_) {
        return true;
    }

    this->handle_ = open("/dev/i2c-1", O_RDWR);

    if (this->handle_ < 0) {
        fmt::print(stderr, "Error opening I2C interface! ({})\n", strerror(errno));
        return false;
    }

    initialized_ = true;
    return true;
}

bool i2c::select(uint8_t address) {
    if (ioctl(this->handle_, I2C_SLAVE, address) < 0) {
        fmt::print(stderr, "Error initializing I2C interface! {}\n", strerror(errno));
        return false;
    }

    return true;
}

bool i2c::receive(uint8_t* buffer, uint32_t size) {
    if (ssize_t err = read(this->handle_, buffer, size); err < 0) {
        fmt::print(stderr, "Error receiving data ({})\n", strerror(errno));

        return false;
    }

    return true;
}

bool i2c::transmit(uint8_t* data, uint32_t size) {
    if (ssize_t err = write(this->handle_, data, size); err < 0) {
        fmt::print(stderr, "Error transmitting data ({})\n", strerror(errno));

        return false;
    }

    return true;
}

bool i2c::terminate() {
    if (int err = close(this->handle_); err < 0) {
        return false;
    }

    return true;
}