cmake_minimum_required(VERSION 3.13)
project(rtos_greenhouse C CXX ASM)

set(CMAKE_CURRENT_LIST_DIR "${CMAKE_SOURCE_DIR}")
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

set(PICO_BOARD pico)


add_library(freertos STATIC
    FreeRTOS-Kernel/tasks.c
    FreeRTOS-Kernel/queue.c
    FreeRTOS-Kernel/list.c
    FreeRTOS-Kernel/timers.c
    FreeRTOS-Kernel/event_groups.c
    FreeRTOS-Kernel/croutine.c
    FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/port.c
    FreeRTOS-Kernel/portable/MemMang/heap_3.c
)

target_include_directories(freertos PUBLIC
    freertos_config
    FreeRTOS-Kernel/include
    FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_timer/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_sync/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_exception/include
    ${PICO_SDK_PATH}/src/common/pico_base_headers/include
    ${PICO_SDK_PATH}/src/common/pico_stdlib_headers/include
)

target_link_libraries(freertos PUBLIC
    pico_stdlib
    hardware_gpio
    hardware_timer
    hardware_irq
    hardware_adc
    hardware_exception   
    pico_unique_id
)

#=========================================================
add_executable(rtos_greenhouse
    src/main.c
    src/sensor.c
    src/controller.c
    src/pump.c
    src/valve.c
    src/utils.c
)

target_include_directories(rtos_greenhouse PRIVATE
    header
    FreeRTOS-Kernel/include
    FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_irq/include
)

target_link_libraries(rtos_greenhouse PRIVATE
    freertos
    pico_stdlib
    hardware_gpio
    hardware_timer
    hardware_adc
    hardware_irq
)
set_target_properties(rtos_greenhouse PROPERTIES OUTPUT_NAME "rtos_greenhouse.elf")

pico_enable_stdio_usb(rtos_greenhouse 1)
pico_enable_stdio_uart(rtos_greenhouse 1)
pico_add_extra_outputs(rtos_greenhouse)
