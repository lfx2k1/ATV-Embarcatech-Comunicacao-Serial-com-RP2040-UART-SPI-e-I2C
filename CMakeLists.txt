cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(main 
    main.c 
    inc/ssd1306.c
    ws2812_library.c
    botao_led_library.c  # Adiciona o arquivo botao_led_library.c
)

pico_set_program_name(main "main")
pico_set_program_version(main "0.1")

pico_generate_pio_header(main ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
target_sources(main PRIVATE main.c)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(main 1)
pico_enable_stdio_usb(main 1)

# Add the standard library to the build
target_link_libraries(main 
  PRIVATE
    pico_stdlib
    hardware_pio
    hardware_i2c
)

# Add include directories
target_include_directories(main PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include
  ${PICO_SDK_PATH}/src/rp2_common/pico_include/include
)

# Adiciona o diretório onde o botao_led_library.h está localizado
target_include_directories(main PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/inc  # Certifique-se de que o caminho está correto
)

# Add the standard include files to the build
pico_add_extra_outputs(main)