#ifndef CMD_RANDOM_VALUE_FUNC_HPP
#define CMD_RANDOM_VALUE_FUNC_HPP

/**
 * @file cmd_random_value_func.hpp
 * @author Wuard
 * @brief This function response the random value to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"


String cmd_random_value_func(const uint16_t n);


#endif