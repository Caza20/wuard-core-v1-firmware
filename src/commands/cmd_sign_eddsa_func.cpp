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
    
    uint8_t signature[TR01_ECDSA_EDDSA_SIGNATURE_LENGTH];  // Ed25519 always 64B

    ret = tropic01.eddsaSign((lt_ecc_slot_t) slot, (const uint8_t *)message, msg_len, signature);
    if (ret != LT_OK) {
        response = "ERR:EDDSA_SIGN_FAILED;\n";
        return response;
    }

    // 5) Convert signature to hex
    response = "OK:SIG:";

    char buf[3];
    for (int i = 0; i < TR01_ECDSA_EDDSA_SIGNATURE_LENGTH; i++) {
        sprintf(buf, "%02X", signature[i]);
        response += buf;
    }

    response += ";";
    return response;
}