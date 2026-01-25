add_library(MessageBus
    message_bus.cc
)

target_link_libraries(MessageBus
    STM32_Drivers
    stm32cubemx
)