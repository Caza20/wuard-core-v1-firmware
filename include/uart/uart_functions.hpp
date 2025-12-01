#ifndef UART_FUNCTIONS_HPP
#define UART_FUNCTIONS_HPP

/**
 * @file uart_functions.hpp
 * @author Wuard
 * @brief This function drives the uart functions.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

#include <Arduino.h>

//* Commands
#include "commands/cmd_chip_id_func.hpp"
#include "commands/cmd_fw_version_func.hpp"
#include "commands/cmd_bootloader_version_func.hpp"
#include "commands/cmd_secure_session.hpp"
#include "commands/cmd_encode_text_func.hpp"
#include "commands/cmd_random_value_func.hpp"
#include "commands/cmd_generate_key_func.hpp"

/* ---------------- UART 1 ---------------- */
#define LT_UART_PORT uart1
#define UART_BAUDRATE 115200  

// UART pins (adjust them to your actual connection)
#define UART_TX_PIN 8   // GPIO8 → UART1_TX
#define UART_RX_PIN 9   // GPIO9 → UART1_RX

/*------------------------------------------*/

class uartFunctions {
    public:
        void begin(int tx, int rx, uint32_t baud, uart_inst_t* uart_id);

        //* UART functions
        void sendData(const String& data);
        String readData();

        //* Commands
        void processCommand(const String &commands);

    private:
        SerialUART* serialPort;
        String inputDataBuffer = "";

        //* Commands
        enum CommandId { 
            CMD_UNKNOWN, 
            CMD_CHIP_ID, 
            CMD_FW_VERSION, 
            CMD_BOOTLOADER_VERSION,
            CMD_SECURE_SESSION_ON,
            CMD_SECURE_SESSION_OFF,
            CMD_ENCODE_TEXT,
            CMD_RANDOM_VALUE,
            CMD_GENERATE_KEY,
            CMD_READ_KEY,
        };

        CommandId parseCommand(const String &cmd);
        void handleCommand(CommandId id, const String &originalCmd);
};


#endif