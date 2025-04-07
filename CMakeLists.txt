cmake_minimum_required( VERSION 3.16)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_SDK_PATH "/home/dpoyesac/Projects/pico/pico-sdk")
include(pico_sdk_import.cmake)

project(bmp280_i2c C CXX ASM)

pico_sdk_init()

# add_library(aht20_i2c
#   aht20_i2c.c
#   aht20_i2c.h
# )

add_library(bmp280_i2c 
    bmp280_i2c.c
    bmp280_i2c.h
    aht20_i2c.c
    aht20_i2c.h
    )

target_link_libraries(bmp280_i2c 
        pico_stdlib
        hardware_i2c
)

target_include_directories(bmp280_i2c PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
