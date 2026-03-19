# DigiSynth

A digital hardware synthesizer built on three cooperating embedded units. A Raspberry Pi Zero 2W acts as the central controller, coordinating a keyboard input unit and an audio synthesis unit over I2C and SPI respectively.

## Architecture

```
┌─────────────────┐     SPI      ┌─────────────────┐     I2S     ┌──────────┐
│  Central Unit   │◄────────────►│   Audio Unit    │────────────►│ WMCU1336 │
│ Raspberry Pi    │              │  STM32F401CCU6  │             │   DAC    │
│   Zero 2W       │              │  (Cortex-M4)    │             └──────────┘
│                 │     I2C      └─────────────────┘
│                 │◄────────────►┌─────────────────┐
│                 │              │  Keyboard Unit  │
│                 │              │  STM32F103C8T6  │
│                 │              │  (Cortex-M3)    │
│                 │              └─────────────────┘
│                 │     I2C
│                 │◄────────────►┌──────────────┐
└─────────────────┘              │ SSD1306 OLED │
                                 │  128×32 px   │
                                 └──────────────┘
```

### Central Unit — Raspberry Pi Zero 2W (`central_unit/`)

Runs Linux (ARMv8). Orchestrates the other units, drives the OLED display, and exposes the synthesizer UI.

- SSD1306 OLED driver over I2C, with three bitmap fonts (7×10, 11×18, 16×26)
- pigpio-based I2C and GPIO interface
- GPIO interrupt on pin 4 for keyboard events
- Built with CMake + Conan; cross-compiled for `aarch64` from an `x86_64` CI host

**Dependencies**: `fmt/12.1.0`, `pigpio/79` (custom Conan recipe in `conan/pigpio/`)

### Audio Unit — STM32F401CCU6 (`audio_unit/`)

Cortex-M4 at 84 MHz. Responsible for all audio synthesis and DAC output.

- I2S output to WMCU1336 DAC at 44.1 kHz stereo 16-bit via DMA circular buffer
- ADSR envelope: reads Attack, Decay, Sustain, Release from four ADC-connected potentiometers
- Sine wave oscillator implemented
- SPI message bus interface to central unit
- UART debug output

### Keyboard Unit — STM32F103C8T6 (`keyboard_unit/`)

Cortex-M3 at 72 MHz. Captures 12 button presses via GPIO external interrupts and forwards them to the central unit over I2C.

- 12 buttons on GPIO external interrupts
- I2C slave interface

## Current State

| Area | Status |
|---|---|
| Central unit OLED display | Working |
| Central unit I2C / GPIO | Working |
| Audio unit hardware init (clock, DMA, I2S, ADC) | Working |
| Audio unit ADSR envelope reading | Working |
| Audio unit sine wave generation | Implemented, not yet triggered |
| Keyboard unit GPIO interrupt handling | Implemented |
| Keyboard unit → central unit messaging | Not connected |
| Central unit → audio unit messaging (SPI) | Initialized, not connected |
| Note triggering (button → oscillator) | Not implemented |
| Synthesizer signal flow end-to-end | Not implemented |
| Display UI for synth parameters | Not implemented |

The hardware abstraction layers for all three units are in place. The missing work is connecting them: routing keyboard events to audio parameters, triggering notes, and building the display UI.

## Building

All three units are built and tested in CI (GitLab CI, see `.gitlab-ci.yml`). Each unit has its own Docker-based cross-compilation environment.

### Central Unit

Requires Conan 2 and a `aarch64-linux-gnu` cross-compiler.

```sh
cd central_unit
conan profile detect --force
conan export conan/pigpio --name=pigpio --version=79
conan install . --profile:host=conan/rpi.ci.profile --profile:build=default --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

### Audio Unit / Keyboard Unit

Requires `arm-none-eabi-gcc`.

```sh
cd audio_unit   # or keyboard_unit
cmake --preset Debug
cmake --build --preset Debug
```

## Hardware

| Component | Role |
|---|---|
| Raspberry Pi Zero 2W | Central controller |
| STM32F401CCU6 | Audio synthesis |
| STM32F103C8T6 | Keyboard input |
| WMCU1336 | I2S DAC, audio output |
| SSD1306 | 128×32 OLED display |
| 12× push buttons | Note input (one octave) |
| 4× potentiometers | ADSR envelope control |

The schematic can be viewed [here](./schematic.pdf).
