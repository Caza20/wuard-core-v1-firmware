#ifndef CMD_SECURE_SESSION_FUNC_HPP
#define CMD_SECURE_SESSION_FUNC_HPP

/**
 * @file cmd_secure_session.hpp
 * @author Wuard
 * @brief This function response the secure session to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include <LibtropicArduino.h>

#include "tropic01/tropic01.h"

// extern session_state_t state;

String cmd_secure_session_func(bool flag);


#endif