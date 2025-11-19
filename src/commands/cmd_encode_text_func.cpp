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

String cmd_encode_text_func(const char* text) {
    String response = "";

    lt_ret_t ret;

    // Now we can use lt_ping() to send a message to TROPIC01 and receive a response, this is done with separate API
    // calls
    uint8_t recv_buf[strlen(text)]; // +1 for null terminator
    // Executing lt_out__ping() with message
    ret = lt_out__ping(&__lt_handle__, (const uint8_t *)text, strlen(text));
    if (LT_OK != ret) {
        // lt_out__ping failed, lt_ret_verbose(ret));
        response = "ERR:FAILED_TO_SEND_PING\n";
        return response;
    }

    // Executing lt_l2_send_encrypted_cmd()...
    ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (LT_OK != ret) {
        // lt_l2_send_encrypted_cmd failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_SEND_ENCRYPTED_CMD\n";
        return response;
    }

    // Executing lt_l2_recv_encrypted_res()...
    ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (LT_OK != ret) {
        // lt_l2_recv_encrypted_res failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_RECV_ENCRYPTED_RES\n";
        return response;
    }

    // Executing lt_in__ping()...
    ret = lt_in__ping(&__lt_handle__, recv_buf, strlen(text));
    if (LT_OK != ret) {
        // lt_in__ping failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_RECEIVE_PING\n";
        return response;
    }

    // add terminator character
    recv_buf[strlen(text)] = '\0';

    response = String("TROPIC01:") + (char*)recv_buf + ";";
    return response;


}