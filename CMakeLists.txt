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
project(STM32F1_HAL)
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
    # Core Source files
    ${PROJ_PATH}/Core/Src/main.c
    ${PROJ_PATH}/Core/Src/printf_redirect.c
    ${PROJ_PATH}/Core/Src/stm32f1xx_it.c
    ${PROJ_PATH}/Core/Src/system_stm32f1xx.c
    # HAL Driver
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
    ${PROJ_PATH}/HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    # Peripherals
    ${PROJ_PATH}/Peripherals/Src/adc.c
    ${PROJ_PATH}/Peripherals/Src/exti.c
    ${PROJ_PATH}/Peripherals/Src/gpio.c
    ${PROJ_PATH}/Peripherals/Src/rcc.c
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
    ${PROJ_PATH}/Core/Inc
    ${PROJ_PATH}/CMSIS/Include
    ${PROJ_PATH}/CMSIS/Device
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