#include "commands/cmd_random_value_func.hpp"

/**
 * @file cmd_random_value_func.cpp
 * @author Wuard
 * @brief This function response the random_value to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_random_value_func(const uint16_t n) {
    String response = "";

    lt_ret_t ret;

    ret = lt_out__random_value_get(&__lt_handle__, n);
    if (LT_OK != ret) {
        // lt_out__random_value_get failed, lt_ret_verbose(ret));
        response = "ERR:FAILED_TO_GET_RANDOM_VALUE;\n";
        return response;
    }

    // Executing lt_l2_send_encrypted_cmd()...
    ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (LT_OK != ret) {
        // lt_l2_send_encrypted_cmd failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_SEND_ENCRYPTED_CMD;\n";
        return response;
    }

    // Executing lt_l2_recv_encrypted_res()...
    ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (LT_OK != ret) {
        // lt_l2_recv_encrypted_res failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_RECV_ENCRYPTED_RES;\n";
        return response;
    }

    uint8_t random_buff[n];

    ret = lt_in__random_value_get(&__lt_handle__, random_buff, n);
    if (ret != LT_OK) {
        // lt_in__random_value_get failed, lt_ret_verbose(ret)
        response = "ERR:FAILED_TO_RECEIVE_RANDOM_VALUE;\n";
        return response;
    }

    response = "OK:RANDOM_VALUE:";

    for (int i=0; i<n; i++) {
        response += String(random_buff[i], HEX);
    }

    response += ";";

    return response;
}