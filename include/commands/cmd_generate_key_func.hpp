#ifndef CMD_GENERATE_KEY_FUNC_HPP
#define CMD_GENERATE_KEY_FUNC_HPP

/**
 * @file cmd_generate_key_func.hpp
 * @author Wuard
 * @brief This function response the generate key to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"


String cmd_generate_key_func(uint8_t slot);

String cmd_read_key_func(uint8_t slot);


#endif