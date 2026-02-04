#include "commands/cmd_generate_key_func.hpp"

/**
 * @file cmd_generate_key_func.cpp
 * @author Wuard
 * @brief This function response the generate key to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_generate_key_func(uint8_t slot) {
    String response = "";

    lt_ret_t ret;

    // 1) Generate ECC key pair in TROPIC01
    // ECC_SLOT_0 = 0 -> First slot
    // ECC_SLOT_1 = 1 -> Second slot
    // .....
    // ECC_SLOT_31 = 31 -> Last slot
    ret = tropic01.eccKeyGenerate((lt_ecc_slot_t)slot, TR01_CURVE_ED25519);
    if (ret != LT_OK) {
        response = "ERR:FAILED_TO_GENERATE_KEY;\n";
        return response;
    }
    // ret = lt_out__ecc_key_generate(&__lt_handle__, ecc_slot_t (slot), CURVE_ED25519);
    // if (ret != LT_OK) {
    //     return "ERR:FAILED_OUT;\n";
    // }

    // // Send and receive via L2
    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // // Decode response
    // ret = lt_in__ecc_key_generate(&__lt_handle__);
    // if (ret != LT_OK) {
    //     return "ERR:FAILED_IN;\n";
    // }



    // 2) Read the newly generated public key
    String read_response = cmd_read_key_func(slot);
    if (read_response.startsWith("ERR")) {
        return read_response;  // Return the error if reading the key failed
    }

    // 3) Convert public key to HEX string
    response = "OK:KEY:";

    response += read_response.substring(7); // Skip "OK:KEY:"

    return response;
}


String cmd_read_key_func(uint8_t slot) {
    String response = "";

    lt_ret_t ret;

    // Read the newly generated public key
    uint8_t pubkey[TR01_CURVE_ED25519_PUBKEY_LEN];
    lt_ecc_curve_type_t curveType;
    lt_ecc_key_origin_t keyOrigin;
    // libtropic defines the slot as ECC_SLOT_0, ECC_SLOT_1, ..., ECC_SLOT_31
    // this function uses the slot number directly
    ret = tropic01.eccKeyRead((lt_ecc_slot_t) slot, pubkey, sizeof(pubkey), curveType, keyOrigin);
    if (ret != LT_OK) {
        response = "ERR:FAILED_TO_READ_KEY;\n";
        return response;
    }
    // ret = lt_out__ecc_key_read(&__lt_handle__, ecc_slot_t (slot));
    // if (ret != LT_OK) {
    //     return "ERR:READ_OUT;\n";
    // }

    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // ret = lt_in__ecc_key_read(&__lt_handle__, pubkey, &curve, &origin);
    // if (ret != LT_OK) {
    //     return "ERR:READ_IN;\n";
    // }

    // Convert public key to HEX string
    response = "OK:KEY:";

    char buf[3];
    for (int i = 0; i < 32; i++) {
        sprintf(buf, "%02X", pubkey[i]);
        response += buf;
    }

    response += ";";

    return response;
}

String cmd_erase_key_func(uint8_t slot) {
    String response = "";

    lt_ret_t ret;

    // Erase ECC key pair in TROPIC01
    // ECC_SLOT_0 = 0 -> First slot
    // ECC_SLOT_1 = 1 -> Second slot
    // .....
    // ECC_SLOT_31 = 31 -> Last slot
    ret = tropic01.eccKeyErase((lt_ecc_slot_t) slot);
    if (ret != LT_OK) {
        response = "ERR:FAILED_TO_ERASE_KEY;\n";
        return response;
    }
    // ret = lt_out__ecc_key_erase(&__lt_handle__, ecc_slot_t (slot));
    // if (ret != LT_OK) {
    //     return "ERR:ERASE_OUT;\n";
    // }

    // // Send and receive via L2
    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // // Decode response
    // ret = lt_in__ecc_key_erase(&__lt_handle__);
    // if (ret != LT_OK) {
    //     return "ERR:ERASE_IN;\n";
    // }

    response = "OK:KEY_ERASED;";

    return response;
}