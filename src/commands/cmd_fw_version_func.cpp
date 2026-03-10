#include "commands/cmd_fw_version_func.hpp"

/**
 * @file cmd_fw_version_func.cpp
 * @author Wuard
 * @brief This function response the firmware version to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************



String cmd_riscv_fw_version_func() {
    String response = "";

    // This variable is reused on more places in this example to store different firmware versions
    uint8_t fw_ver[TR01_L2_GET_INFO_RISCV_FW_SIZE] = {0};

    lt_ret_t ret = tropic01.getRiscvFWVersion(fw_ver);
    if (ret == LT_OK) {
        response = tropic01.printRiscvFWVersion(fw_ver);
    }
    else {
        response = "ERR:FAILED_TO_GET_RISCV_FW_VERSION;\n";
        lt_deinit(tropic01.getHandle());
    }

    return response;
}

String cmd_spect_fw_version_func() {
    String response = "";

    // This variable is reused on more places in this example to store different firmware versions
    uint8_t fw_ver[TR01_L2_GET_INFO_RISCV_FW_SIZE] = {0};

    lt_ret_t ret = tropic01.getSpectFWVersion(fw_ver);
    if (ret == LT_OK) {
        response = tropic01.printSpectFWVersion(fw_ver);
    }
    else {
        response = "ERR:FAILED_TO_GET_SPECT_FW_VERSION;\n";
        lt_deinit(tropic01.getHandle());
    }

    return response;
}