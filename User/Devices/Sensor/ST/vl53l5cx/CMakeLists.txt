cmake_minimum_required(VERSION 3.22)

project(vl53l5cx_sensor_api)
add_library(vl53l5cx_sensor_api INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(vl53l5cx_sensor_api INTERFACE
	USE_HAL_DRIVER
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(vl53l5cx_sensor_api INTERFACE
    Core/Inc
    Platform/Inc
)

target_sources(vl53l5cx_sensor_api INTERFACE
    Core/Src/vl53l5cx_api.c
    Core/Src/vl53l5cx_plugin_detection_thresholds.c
    Core/Src/vl53l5cx_plugin_motion_indicator.c
    Core/Src/vl53l5cx_plugin_xtalk.c
    Platform/Src/vl53l5cx_platform.c
)

target_link_directories(vl53l5cx_sensor_api INTERFACE
)

target_link_libraries(vl53l5cx_sensor_api INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
