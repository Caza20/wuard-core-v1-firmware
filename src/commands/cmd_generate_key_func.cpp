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

    // Convert public key to HEX string
    response = "OK:KEY:";

    char buf[3];
    for (int i = 0; i < TR01_CURVE_ED25519_PUBKEY_LEN; i++) {
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

    response = "OK:KEY_ERASED;";

    return response;
}