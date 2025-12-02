#ifndef CMD_SIGN_EDDSA_FUNC_HPP
#define CMD_SIGN_EDDSA_FUNC_HPP

/**
 * @file cmd_sign_eddsa_func.hpp
 * @author Wuard
 * @brief This function response the sign eddsa to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"


String cmd_sign_eddsa_func(uint8_t slot, const uint8_t* message, uint16_t msg_len);


#endif  