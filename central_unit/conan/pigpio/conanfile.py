from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class PigpioRecipe(ConanFile):
    name = "pigpio"
    version = "79"
    license = "MIT"
    url = "https://github.com/joan2937/pigpio"
    description = "C library for Raspberry Pi GPIO"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def source(self):
        self.run(f"git clone --branch v{self.version} https://github.com/joan2937/pigpio.git src")

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="src", variables={"CMAKE_POLICY_VERSION_MINIMUM": "3.5"})
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.components["pigpio"].libs = ["pigpio"]
        self.cpp_info.components["pigpiod_if"].libs = ["pigpiod_if"]
        self.cpp_info.components["pigpiod_if2"].libs = ["pigpiod_if2"]