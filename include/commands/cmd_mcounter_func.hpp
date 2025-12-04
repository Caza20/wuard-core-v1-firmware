#ifndef CMD_MCOUNTER_FUNC_HPP
#define CMD_MCOUNTER_FUNC_HPP

/**
 * @file cmd_mcounter_func.hpp
 * @author Wuard
 * @brief This function response the mcounter to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"


String cmd_mcounter_init_func(uint8_t index, uint32_t value);
String cmd_mcounter_get_func(uint8_t index);
String cmd_mcounter_update_func(uint8_t index);

#endif