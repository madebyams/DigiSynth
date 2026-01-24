# DigiSynth

A digital hardware syntheseizer.

## Components

### Processing
- Raspberry Pi Zero 2W 
    - Central Unit
    - Communicates between the Audio Unit (STMF401CCU6) via SPI and the Keyboard Unit (STM32F103C8T6) via I2C
    - Also takes care of display (SSD1306)
- STM32F401CCU6
    - The Audio Unit
    - Responsible for synthesis
    - Sends produed audio waves to DAC (WMCU1336) via I2S
- STM32F103C8T6
    - The Keyboard Unit
    - Connected to 12 Buttons representing a keyboard
    - Sends control signals to the Central Unit via EXT GPIO Interrupt and I2C

### User Interface
- SSD1306 OLED Display

### Audio
- WMCU1336 I2S DAC

### User Controls
- 12 Push Buttons
- 4 Potentiometers for ADSR Envelope

## Schematic

The schematic for the project can be viewed [here](./schematic.pdf)