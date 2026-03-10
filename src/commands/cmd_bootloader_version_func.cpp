#include "commands/cmd_bootloader_version_func.hpp"

/**
 * @file cmd_bootloader_version_func.cpp
 * @author Wuard
 * @brief This function response the bootloader version to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_bootloader_version_func() {

    String response = "";

    uint8_t fw_ver[TR01_L2_GET_INFO_RISCV_FW_SIZE] = {0};

    lt_ret_t res = tropic01.getBootloaderFWVersion(fw_ver);
    if (res != LT_OK) {
      response = "ERR:FW_VERSION_FAIL;\n";
      return response;
    }

    response = tropic01.printBootloaderVersion(fw_ver);

    return response;
}

