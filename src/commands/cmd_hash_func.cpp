#include "commands/cmd_hash_func.hpp"

/**
 * @file cmd_hash_func.cpp
 * @author Wuard
 * @brief This function response the hash to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_hash_func(const uint8_t *msg, const uint32_t msg_len) {
    String response = "";

    // Prepare hash of a message
    uint8_t msg_hash[32] = {0};
    struct lt_crypto_sha256_ctx_t hctx;
    lt_sha256_init(&hctx);
    lt_sha256_start(&hctx);
    lt_sha256_update(&hctx, (uint8_t *)msg, msg_len);
    lt_sha256_finish(&hctx, msg_hash);

    response = "OK:hash:0x";

    char buf[3]; // 2 hex chars + null
    for (size_t i = 0; i < sizeof(msg_hash); i++) {
        sprintf(buf, "%02X", msg_hash[i]);
        response += buf;
    }

    response += ";";

    return response;
}