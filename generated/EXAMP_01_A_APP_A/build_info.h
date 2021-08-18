#ifndef __BUILD_INFO_H__
#define __BUILD_INFO_H__

#include <stdint.h>

/**
 * Build info
 * */
#define PROJECT_NAME                "EXAMP_01"
#define FW_VERSION                  "0.1.0"
#define BOARD_MCU                   'A'
#define BOARD_REVISION              'A'
#define BUILD_TIMESTAMP             1628024040UL
#define GIT_CURRENT_BRANCH          "master"
#define GIT_IS_MASTER_BRANCH        1U
#define GIT_REVISION_FULL           "ab134661-dirty"
#define GIT_REVISION_SHORT          0xab134661UL

/**
 * Memory layout
 * */
#define MCU_FLASH_KB                64UL
#define MCU_RAM_KB                  12UL

/**
 * Section sizes and their addresses
 * */
#define BOOT_ORIGIN                 0x8000000UL
#define SETT_ORIGIN                 0x800f800UL
#define APPL_ORIGIN                 0x8000000UL

#define BOOT_SIZE_KB                0UL
#define SETT_SIZE_KB                2UL
#define APPL_SIZE_KB                62UL

#endif // __BUILD_INFO_H__
