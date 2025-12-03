#ifndef CMD_HASH_FUNC_HPP
#define CMD_HASH_FUNC_HPP

/**
 * @file cmd_hash_func.hpp
 * @author Wuard
 * @brief This function response the hash to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"
extern "C" {
    #include "lt_sha256.h" // to do the hash
}


String cmd_hash_func(const uint8_t *msg, const uint32_t msg_len);


#endif