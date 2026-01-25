add_library(DMA
    dma.cc
)

target_link_libraries(DMA
    STM32_Drivers
    stm32cubemx
)