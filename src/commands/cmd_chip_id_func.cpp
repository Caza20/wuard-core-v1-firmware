#include "commands/cmd_chip_id_func.hpp"

/**
 * @file cmd_chip_id_func.cpp
 * @author Wuard
 * @brief This function response the chip id to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_chip_id_func() {

    String response = "";

    lt_chip_id_t chip_id = {0};

    lt_ret_t res = tropic01.getChipID(chip_id);

    if (res != LT_OK) {
        response = "ERR:CHIP_ID_FAIL;\n";
        return response;
    } 

    response = tropic01.printChipID(chip_id);

    return response;
}