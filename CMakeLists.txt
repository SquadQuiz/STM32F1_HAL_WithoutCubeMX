cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
message("Build type: "              ${CMAKE_BUILD_TYPE})

#
# Core project settings
#
project(STM32F1_HAL_WithoutCubeMX)
enable_language(C CXX ASM)

#
# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
#
set(CPU_PARAMETERS
    -mthumb

    # This needs attention to properly set for used MCU
    -mcpu=cortex-m3
    -mfloat-abi=soft
)

# Set linker script
set(linker_script_SRC               ${PROJ_PATH}/STM32F103C8TX_FLASH.ld)
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})

#
# List of source files to compile
#
set(sources_SRCS
    # Put here your source files, one in each line, relative to CMakeLists.txt file location
    # Application
    # IMU MPU6050
    ${PROJ_PATH}/Application/MPU6050/TJ_MPU6050.c
    # RFID RC522
    ${PROJ_PATH}/Application/RC522/rc522.c
    # SDCARD
    ${PROJ_PATH}/Application/SdCard/fatfs_sd.c
    ${PROJ_PATH}/Application/SdCard/fatfs.c
    ${PROJ_PATH}/Application/SdCard/sd_driver.c
    ${PROJ_PATH}/Application/SdCard/user_diskio.c
    # USB MSC
    ${PROJ_PATH}/Application/USB_MSC/usb_device.c
    ${PROJ_PATH}/Application/USB_MSC/usbd_conf.c
    ${PROJ_PATH}/Application/USB_MSC/usbd_desc.c
    ${PROJ_PATH}/Application/USB_MSC/usbd_storage_if.c
    # FreeROTS
    ${PROJ_PATH}/Application/RTOS/freertos.c
    # Core Source files
    ${PROJ_PATH}/Core/Src/main.c
    ${PROJ_PATH}/Core/Src/printf_redirect.c
    ${PROJ_PATH}/Core/Src/stm32f1xx_it.c
    ${PROJ_PATH}/Core/Src/syscalls.c
    ${PROJ_PATH}/Core/Src/sysmem.c
    ${PROJ_PATH}/Core/Src/system_stm32f1xx.c
    # HAL Driver
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
    # Middleware
    # FatFs
    ${PROJ_PATH}/Middleware/FatFs/diskio.c
    ${PROJ_PATH}/Middleware/FatFs/ff_gen_drv.c
    ${PROJ_PATH}/Middleware/FatFs/ff.c
    # STM32_USB_Device_Library
    # STM32_USB_Device_Library/Class
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_bot.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_data.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_scsi.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c
    # STM32_USB_Device_Library/Core
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Core/Src/usbd_core.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
    # FreeRTOS
    ${PROJ_PATH}/Middleware/FreeRTOS/croutine.c
    ${PROJ_PATH}/Middleware/FreeRTOS/event_groups.c
    ${PROJ_PATH}/Middleware/FreeRTOS/list.c
    ${PROJ_PATH}/Middleware/FreeRTOS/queue.c
    ${PROJ_PATH}/Middleware/FreeRTOS/stream_buffer.c
    ${PROJ_PATH}/Middleware/FreeRTOS/tasks.c
    ${PROJ_PATH}/Middleware/FreeRTOS/timers.c
    # CMSIS_RTOS
    ${PROJ_PATH}/Middleware/FreeRTOS/CMSIS_RTOS/cmsis_os.c
    # portable/GCC/ARM_CM3
    ${PROJ_PATH}/Middleware/FreeRTOS/portable/GCC/ARM_CM3/port.c
    # portable/GCC/MemMang
    ${PROJ_PATH}/Middleware/FreeRTOS/portable/MemMang/heap_4.c
    # Peripherals
    ${PROJ_PATH}/Peripherals/Src/adc.c
    ${PROJ_PATH}/Peripherals/Src/crc.c
    ${PROJ_PATH}/Peripherals/Src/exti.c
    ${PROJ_PATH}/Peripherals/Src/gpio.c
    ${PROJ_PATH}/Peripherals/Src/i2c.c
    ${PROJ_PATH}/Peripherals/Src/pwr.c
    ${PROJ_PATH}/Peripherals/Src/rcc.c
    ${PROJ_PATH}/Peripherals/Src/rtc.c
    ${PROJ_PATH}/Peripherals/Src/spi.c
    ${PROJ_PATH}/Peripherals/Src/tim.c
    ${PROJ_PATH}/Peripherals/Src/uart.c
    # Startup
    ${PROJ_PATH}/Startup/startup_stm32f103xb.s

)

#
# Include directories
#
set(include_path_DIRS
    # Put here your include dirs, one in each line, relative to CMakeLists.txt file location
    ${PROJ_PATH}/Application/MPU6050
    ${PROJ_PATH}/Application/RC522
    ${PROJ_PATH}/Application/RTOS
    ${PROJ_PATH}/Application/SdCard
    ${PROJ_PATH}/Application/USB_MSC
    ${PROJ_PATH}/Core/Inc
    ${PROJ_PATH}/CMSIS/Include
    ${PROJ_PATH}/CMSIS/Device
    ${PROJ_PATH}/Middleware/FatFs
    ${PROJ_PATH}/Middleware/FreeRTOS/CMSIS_RTOS
    ${PROJ_PATH}/Middleware/FreeRTOS/include
    ${PROJ_PATH}/Middleware/FreeRTOS/portable/GCC/ARM_CM3
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Inc
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Class/MSC/Inc
    ${PROJ_PATH}/Middleware/STM32_USB_Device_Library/Core/Inc
    ${PROJ_PATH}/Peripherals/Inc
    ${PROJ_PATH}/HAL
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Inc
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Inc/Legacy
)

#
# Symbols definition
#
set(symbols_SYMB
    # Put here your symbols (preprocessor defines), one in each line
    # Encapsulate them with double quotes for safety purpose
    "DEBUG"
    "STM32F103xB"
    "USE_HAL_DRIVER"
)

# Executable files
add_executable(${EXECUTABLE} ${sources_SRCS})

# Include paths
target_include_directories(${EXECUTABLE} PRIVATE ${include_path_DIRS})

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    # Full debug configuration
    -Og -g3 -ggdb
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
    -T${linker_script_SRC}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)