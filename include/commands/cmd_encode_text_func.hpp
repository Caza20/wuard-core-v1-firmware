#ifndef CMD_ENCODE_TEXT_FUNC_HPP
#define CMD_ENCODE_TEXT_FUNC_HPP

/**
 * @file cmd_encode_text_func.hpp
 * @author Wuard
 * @brief This function response the encode text to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include <LibtropicArduino.h>

#include "tropic01/tropic01.h"


String cmd_encode_text_func(const char* text, size_t len);


#endif