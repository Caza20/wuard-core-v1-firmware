#ifndef CMD_BOOTLOADER_VERSION_FUNC_HPP
#define CMD_BOOTLOADER_VERSION_FUNC_HPP

/**
 * @file cmd_bootloader_version_func.hpp
 * @author Wuard
 * @brief This function response the bootloader version to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include <LibtropicArduino.h>

#include "tropic01/tropic01.h"


String cmd_bootloader_version_func();


// -------

// String get_headers_v1(lt_handle_t* handle);
// String header_boot_v2_0_1(uint8_t *data, lt_bank_id_t bank_id);

// String get_headers_v2(lt_handle_t* handle);
// String header_boot_v1_0_1(uint8_t *data, lt_bank_id_t bank_id);


#endif