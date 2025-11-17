#ifndef CMD_SECURE_SESSION_HPP
#define CMD_SECURE_SESSION_HPP

/**
 * @file cmd_secure_session.hpp
 * @author Wuard
 * @brief This function response the secure session to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include "libtropic_platfomio.hpp"


String cmd_secure_session_func(bool flag);


#endif