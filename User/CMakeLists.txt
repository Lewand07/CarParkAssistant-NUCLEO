cmake_minimum_required(VERSION 3.22)

project(car_assistant_lib)
add_library(car_assistant_lib INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(car_assistant_lib INTERFACE
	USE_HAL_DRIVER
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(car_assistant_lib INTERFACE
    Interfaces/Inc
    Adapters/Inc
    Setup/Inc
)

target_sources(car_assistant_lib INTERFACE
    Interfaces/Src/servo_interface.c
    Adapters/Src/servo_mg996r_adapter.c
    Interfaces/Src/motor_interface.c
    Adapters/Src/motor_mx1508_adapter.c
    Interfaces/Src/sensor_interface.c
    Adapters/Src/sensor_vl53lx_adapter.c
    Adapters/Src/sensor_vl53l5cx_adapter.c
    Interfaces/Src/car_interface.c
    Setup/Src/car_setup.c
)

target_link_directories(car_assistant_lib INTERFACE
)

target_link_libraries(car_assistant_lib INTERFACE
)

# Validate that car_assistant_lib code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
