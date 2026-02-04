#include "commands/cmd_encode_text_func.hpp"

/**
 * @file cmd_encode_text_func.cpp
 * @author Wuard
 * @brief This function response the encode_text to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_encode_text_func(const char* text, size_t len) {
    String response = "";

    char recv_buf[len + 1]; // +1 for null terminator
    
    lt_ret_t ret = tropic01.ping(text, recv_buf, len);
    if (LT_OK != ret) {
        response = "ERR:FAILED_TO_ENCODE_TEXT;\n";
        return response;
    }

    // add terminator character
    recv_buf[len] = '\0';

    response = String("OK:TROPIC01:") + recv_buf + ";";
    
    return response;


}