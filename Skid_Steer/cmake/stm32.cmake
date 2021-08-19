set(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(CPU_FLAGS "-mcpu=cortex-m4")

set(HAL_DRIVERS_DIR "STM32F4xx")
set(LINKER_SCRIPT_NAME "STM32F429ZITx_FLASH")

set(OPENOCD_SCRIPT_NAME "STM32F429") 
set(OPENOCD_CPU_FREQ "180000000")

add_definitions(-DSTM32F334x8 -DUSE_HAL_DRIVER)

message(STATUS "Used MCU: STM32f429ZITx")
