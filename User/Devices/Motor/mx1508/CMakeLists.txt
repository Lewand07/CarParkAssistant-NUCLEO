cmake_minimum_required(VERSION 3.22)

project(mx1508_motor_api)
add_library(mx1508_motor_api INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(mx1508_motor_api INTERFACE
	USE_HAL_DRIVER
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(mx1508_motor_api INTERFACE
    Inc
)

target_sources(mx1508_motor_api INTERFACE
    Src/mx1508_motor_api.c
)

target_link_directories(mx1508_motor_api INTERFACE
)

target_link_libraries(mx1508_motor_api INTERFACE
)

# Validate that mx1508_motor_api code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
