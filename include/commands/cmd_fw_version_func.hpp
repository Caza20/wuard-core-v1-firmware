#ifndef CMD_FW_VERSION_FUNC_HPP
#define CMD_FW_VERSION_FUNC_HPP

/**
 * @file cmd_fw_version_func.hpp
 * @author Wuard
 * @brief This function response the firmware version to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */



#include <Arduino.h>
#include <LibtropicArduino.h>

#include "tropic01/tropic01.h"


String cmd_riscv_fw_version_func();
String cmd_spect_fw_version_func();


#endif