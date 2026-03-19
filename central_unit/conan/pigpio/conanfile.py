import os
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
        # Patch broken FindRT.cmake: original unconditionally calls set_target_properties
        # even when RT is not found, which fails during cross-compilation.
        find_rt_path = os.path.join(self.source_folder, "src", "cmake", "FindRT.cmake")
        with open(find_rt_path, "w") as f:
            f.write(
                'find_library(RT_LIBRARIES NAMES rt)\n'
                'if(RT_LIBRARIES)\n'
                '    set(RT_FOUND TRUE)\n'
                '    add_library(RT::RT UNKNOWN IMPORTED)\n'
                '    set_target_properties(RT::RT PROPERTIES IMPORTED_LOCATION "${RT_LIBRARIES}")\n'
                'else()\n'
                '    set(RT_FOUND FALSE)\n'
                '    set(RT_LIBRARIES "")\n'
                'endif()\n'
            )
        cmake = CMake(self)
        cmake.configure(build_script_folder="src", variables={
            "CMAKE_POLICY_VERSION_MINIMUM": "3.5",
        })
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.components["pigpio"].libs = ["pigpio"]
        self.cpp_info.components["pigpiod_if"].libs = ["pigpiod_if"]
        self.cpp_info.components["pigpiod_if2"].libs = ["pigpiod_if2"]
