#include "commands/cmd_secure_session_func.hpp"

/**
 * @file cmd_chip_id_func.cpp
 * @author Wuard
 * @brief This function response the secure session to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_secure_session_func(bool flag) {
    String response = "";

    if (flag) {
        lt_ret_t res = tropic01.secureSessionON(PAIRING_KEY_SLOT, PAIRING_KEY_PRIV, PAIRING_KEY_PUB);
        if (res != LT_OK) {
            response = "ERR:FAILED_TO_ESTABLISH_SESSION;\n";
            return response;
        }

        response = "OK:secure_session;\n";
    } else {
        lt_ret_t res = tropic01.secureSessionOFF();
        if (res != LT_OK) {
            response = "ERR:FAILED_TO_ABORT_SESSION;\n";
            return response;    
        }

        response = "OK:session_aborted;\n";
    }

    return response;
}