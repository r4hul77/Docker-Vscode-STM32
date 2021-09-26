
set(PRJ_VERSION     "${APP_VERSION}")
set(BINARY_NAME "${PRJ_NAME}_${MCU_BOARD}_APP_${BOARD_REV}")
set(LD_FLASH_ORIGIN  "${APPL_ORIGIN}")
set(LD_FLASH_SIZE_KB "${APPL_SIZE_KB}")

set(LD_FLASH_SIZE_KB "${APPL_SIZE_KB}")
include(../cmake/BuildInfo.cmake)

# Собираем библиотеки
# //NOTE: не очень понятно, нужно ли подключать cmsis как библиотеку
add_library(${BINARY_NAME}_CMSIS	Core/Src/system_stm32f4xx.c
									startup_stm32f429xx.s)

# Исходники
file(GLOB_RECURSE SOURCE_GEN		"${CMAKE_BINARY_DIR}/generated/${BINARY_NAME}/*.c")
file(GLOB_RECURSE SOURCES_CORE		"Core/Src/*")
#file(GLOB_RECURSE SOURCES_DSP		"DSP/*")
file(GLOB_RECURSE SOURCES_HAL		"Drivers/${HAL_DRIVERS_DIR}_HAL_Driver/Src/*" "Drivers/CMSIS/Device/ST/${HAL_DRIVERS_DIR}/Source/*")
file(GLOB_RECURSE SOURCES_FAT		"FATFS/*" "Middlewares/Third_Party/*")
file(GLOB_RECURSE SOURCES_USR		"User/src/*" "../General/Src/*")
file(GLOB_RECURSE SOURCES_MICROROS   "Microros/src/*")
file(GLOB_RECURSE SOURCES_ROSMEMORY   "Microros/custom_overrides/*")
message("${SOURCES_MICROROS}=${${SOURCES_MICROROS}}")




# Подключаем директории с которыми придётся работать
include_directories(
		# generated files
		${CMAKE_BINARY_DIR}/generated/${BINARY_NAME}
		# Core
		Core/Inc
		Microros/include
        Microros/custom_overrides/include
		Drivers/CMSIS/Include
		Drivers/CMSIS/Device/ST/${HAL_DRIVERS_DIR}/Include
		# DSP
		#DSP/Inc
		# HAL
		Drivers/${HAL_DRIVERS_DIR}_HAL_Driver/Inc
		FATFS
		FATFS/App
		FATFS/Target
		Middlewares/Third_Party/FatFs/src
        Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
        Middlewares/Third_Party/FreeRTOS/Source/include
        Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
		# User
		User/Inc
		../General/Inc
)

link_directories(Microros)


########## Build
# Configuring the file - compiler script: replace the variables in the file with sizes and addresses
configure_file(../cmake/${LINKER_SCRIPT_NAME}.ld.in ${CMAKE_CURRENT_BINARY_DIR}/linker_script.ld)
set(LINKER_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/linker_script.ld)

# Configure the file - compiler script: replace the variables in the file with sizes and addresses
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}.map,--gc-sections,--undefined=uxTopUsedPriority,--print-memory-usage${LINKER_RELEASE} -T ${LINKER_SCRIPT} ${LINKER_FLAGS}")

# Collecting project sources, modules, etc. in elf
add_executable(${BINARY_NAME}.elf ${SOURCE_GEN}    ${SOURCES_ROSMEMORY}  ${SOURCES_CORE}  ${SOURCES_HAL} ${SOURCES_MICROROS}  ${SOURCES_USR} ${SOURCES_FAT}) # ${SOURCES_DSP}
target_link_libraries(${BINARY_NAME}.elf ${BINARY_NAME}_CMSIS microros)

# Convert elf to hex and bin
set(APP_HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}.hex)
set(APP_BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}.bin)
add_custom_command(TARGET ${BINARY_NAME}.elf POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${BINARY_NAME}.elf> ${APP_HEX_FILE}
		COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${BINARY_NAME}.elf> ${APP_BIN_FILE}
		COMMENT "Building ${APP_HEX_FILE} \nBuilding ${APP_BIN_FILE}")

########## Cleaning 
include(../cmake/Cleaning.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Astyle.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/vscode/vscode.cmake)
