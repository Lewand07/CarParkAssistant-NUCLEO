cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32F767xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../X-CUBE-TOF1/Target
    ../../Drivers/STM32F7xx_HAL_Driver/Inc
    ../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
    ../../Middlewares/Third_Party/FreeRTOS/Source/include
    ../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
    ../../Drivers/CMSIS/Device/ST/STM32F7xx/Include
    ../../Drivers/CMSIS/Include
    ../../Drivers/BSP/Components/vl53l3cx/modules
    ../../Drivers/BSP/Components/vl53l3cx/porting
    ../../Drivers/BSP/Components/vl53l3cx
    ../../Drivers/BSP/Components/vl53l5cx/modules
    ../../Drivers/BSP/Components/vl53l5cx/porting
    ../../Drivers/BSP/Components/vl53l5cx
)

target_sources(stm32cubemx INTERFACE
    ../../Core/Src/main.c
    ../../Core/Src/gpio.c
    ../../Core/Src/freertos.c
    ../../Core/Src/eth.c
    ../../Core/Src/tim.c
    ../../Core/Src/usart.c
    ../../Core/Src/usb_otg.c
    ../../Core/Src/stm32f7xx_nucleo_bus.c
    ../../Core/Src/stm32f7xx_it.c
    ../../Core/Src/stm32f7xx_hal_msp.c
    ../../Core/Src/stm32f7xx_hal_timebase_tim.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_calibration.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_core.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_debug.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_api_preset_modes.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_core_support.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_dmax.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen3.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_algos_gen4.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_char.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_core.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_hist_funcs.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_nvm_debug.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_register_funcs.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_sigma_estimate.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_silicon_core.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_wait.c
    ../../Drivers/BSP/Components/vl53l3cx/modules/vl53lx_xtalk.c
    ../../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform.c
    ../../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_ipp.c
    ../../Drivers/BSP/Components/vl53l3cx/porting/vl53lx_platform_log.c
    ../../Drivers/BSP/Components/vl53l3cx/vl53l3cx.c
    ../../Drivers/BSP/Components/vl53l5cx/modules/vl53l5cx_api.c
    ../../Drivers/BSP/Components/vl53l5cx/modules/vl53l5cx_plugin_detection_thresholds.c
    ../../Drivers/BSP/Components/vl53l5cx/modules/vl53l5cx_plugin_motion_indicator.c
    ../../Drivers/BSP/Components/vl53l5cx/modules/vl53l5cx_plugin_xtalk.c
    ../../Drivers/BSP/Components/vl53l5cx/porting/platform.c
    ../../Drivers/BSP/Components/vl53l5cx/vl53l5cx.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c
    ../../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c
    ../../Core/Src/system_stm32f7xx.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/list.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32f767xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


