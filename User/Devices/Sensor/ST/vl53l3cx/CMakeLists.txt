cmake_minimum_required(VERSION 3.22)

project(vl53l3cx_sensor_api)
add_library(vl53l3cx_sensor_api INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(vl53l3cx_sensor_api INTERFACE
	USE_HAL_DRIVER
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(vl53l3cx_sensor_api INTERFACE
    Core/Inc
    Platform/Inc
)

target_sources(vl53l3cx_sensor_api INTERFACE
    Core/Src/vl53lx_api.c
    Core/Src/vl53lx_api_calibration.c
    Core/Src/vl53lx_api_core.c
    Core/Src/vl53lx_api_debug.c
    Core/Src/vl53lx_api_preset_modes.c
    Core/Src/vl53lx_core.c
    Core/Src/vl53lx_core_support.c
    Core/Src/vl53lx_dmax.c
    Core/Src/vl53lx_hist_algos_gen3.c
    Core/Src/vl53lx_hist_algos_gen4.c
    Core/Src/vl53lx_hist_char.c
    Core/Src/vl53lx_hist_core.c
    Core/Src/vl53lx_hist_funcs.c
    Core/Src/vl53lx_nvm.c
    Core/Src/vl53lx_nvm_debug.c
    Core/Src/vl53lx_register_funcs.c
    Core/Src/vl53lx_sigma_estimate.c
    Core/Src/vl53lx_silicon_core.c
    Core/Src/vl53lx_wait.c
    Core/Src/vl53lx_xtalk.c
    Platform/Src/vl53lx_platform.c
    Platform/Src/vl53lx_platform_init.c
    Platform/Src/vl53lx_platform_ipp.c
    Platform/Src/vl53lx_platform_log.c
)

target_link_directories(vl53l3cx_sensor_api INTERFACE
)

target_link_libraries(vl53l3cx_sensor_api INTERFACE
)

# Validate that vl53l3cx_sensor_api code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
