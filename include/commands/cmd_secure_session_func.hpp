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

// extern session_state_t state;

String cmd_secure_session_func(lt_handle_t* handle, bool flag, const uint8_t *shipriv, const uint8_t *shipub,
                               const lt_pkey_index_t pkey_index);


#endif