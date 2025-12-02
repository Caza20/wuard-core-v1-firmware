#include "commands/cmd_sign_eddsa_func.hpp"

/**
 * @file cmd_sign_eddsa_func.cpp
 * @author Wuard
 * @brief This function response the sign eddsa to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_sign_eddsa_func(uint8_t slot, const uint8_t* message, uint16_t msg_len) {
    String response = "";

    lt_ret_t ret;

    // 1) Encode EDDSA sign
    ret = lt_out__ecc_eddsa_sign(&__lt_handle__, ecc_slot_t(slot), message, msg_len);
    if (ret != LT_OK) { 
        return "ERR:OUT\n";
    }

    // 2) Send to L2
    ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (ret != LT_OK) {
        return "ERR:SEND\n";
    }

    // 3) Receive from L2
    ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    if (ret != LT_OK) {
        return "ERR:RECV\n";
    }

    // 4) Decode
    uint8_t signature[64];  // Ed25519 always 64B
    ret = lt_in__ecc_eddsa_sign(&__lt_handle__, signature);
    if (ret != LT_OK) {
        return "ERR:IN\n";
    }

    // 5) Convert signature to hex
    response = "OK:SIG:";

    char buf[3];
    for (int i = 0; i < 64; i++) {
        sprintf(buf, "%02X", signature[i]);
        response += buf;
    }

    response += ";";
    return response;
}