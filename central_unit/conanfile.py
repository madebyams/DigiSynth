from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CentralUnitRecipe(ConanFile):
    name = "central_unit"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"


    def requirements(self):
        self.requires("fmt/12.1.0")
        self.requires("pigpio/79")

    def layout(self):
        cmake_layout(self)