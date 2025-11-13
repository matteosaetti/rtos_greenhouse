cmake_minimum_required(VERSION 3.19)

include(pico_sdk_import.cmake)
project(blink C CXX ASM)

pico_sdk_init()

add_executable(blink
    src/main.c
)

# --- FreeRTOS core sources ---
file(GLOB FreeRTOS_src FreeRTOS-Kernel/*.c)

add_library(FreeRTOS STATIC
    ${FreeRTOS_src}
    FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/port.c
    FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories(FreeRTOS PUBLIC
    FreeRTOS-Kernel/include
    include/
    FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include
)

target_link_libraries(FreeRTOS PUBLIC 
	pico_stdlib
    hardware_exception
    hardware_irq
    hardware_sync
	hardware_structs
	)

target_link_libraries(blink
    pico_stdlib
    hardware_gpio
    FreeRTOS
)

pico_add_extra_outputs(blink)
