#ifndef CMD_CHIP_ID_FUNC_HPP
#define CMD_CHIP_ID_FUNC_HPP

/**
 * @file cmd_chip_id_func.hpp
 * @author Wuard
 * @brief This function response the chip id to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include <LibtropicArduino.h>


String cmd_chip_id_func(lt_chip_id_t chip_id);


#endif