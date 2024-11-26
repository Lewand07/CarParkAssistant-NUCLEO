cmake_minimum_required(VERSION 3.22)

project(mg996r_servo_api)
add_library(mg996r_servo_api INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(mg996r_servo_api INTERFACE
	USE_HAL_DRIVER
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(mg996r_servo_api INTERFACE
    Inc
)

target_sources(mg996r_servo_api INTERFACE
    Src/mg996r_servo_api.c
)

target_link_directories(mg996r_servo_api INTERFACE
)

target_link_libraries(mg996r_servo_api INTERFACE
)

# Validate that mg996r_servo_api code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
