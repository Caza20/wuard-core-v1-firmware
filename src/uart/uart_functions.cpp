#include "uart/uart_functions.hpp"


void uartFunctions::begin(int tx, int rx, uint32_t baud, uart_inst_t* uart_id) {
    serialPort = nullptr;
    serialPort = new SerialUART(uart_id, tx, rx);
    serialPort->begin(baud, SERIAL_8N1);
}


//**************************************************
//*               UART functions
//************************************************** 

//* Send data via UART
void uartFunctions::sendData(const String& data) {
      if (serialPort) serialPort->print(data);
}

//* Read data from UART
String uartFunctions::readData() {
  if (serialPort) {
    while (serialPort->available()) {
      char c = (char)serialPort->read();
      if (c == ';') {  // end of the command
        String cmd = inputDataBuffer + ";";
        inputDataBuffer = "";
        return cmd;
      } else {
        inputDataBuffer += c;
      }
    }
  }
  return "";  // no data available
}


//**************************************************
//*          Command processing functions
//************************************************** 

//* Función principal: valida formato y procesa cada comando separado por coma
void uartFunctions::processCommand(const String &commands) {
  if (commands.length() == 0) {
    sendData("ERR:EMPTY_COMMAND\n");
    return;
  }

  // To do a copy we can modify
  String s = commands;
  s.trim();
  
  // 1) Validate format: must end with ';'
  if (s.length() == 0 || s.charAt(s.length() - 1) != ';') {
    sendData("ERR:INVALID_FORMAT\n");
    return;
  }

  // 2) Delete the ending ';'
  s = s.substring(0, s.length() - 1);

  // 3) Iterates through tokens separated by "," and processes them one by one
  int start = 0;
  while (start <= s.length()) {
    int commaIdx = s.indexOf(',', start);
    String token;
    if (commaIdx == -1) {
      // last token (or only one)
      token = s.substring(start);
      start = s.length() + 1; // while output
    } else {
      token = s.substring(start, commaIdx);
      start = commaIdx + 1; // move after comma
    }

    token.trim(); // delete leading/trailing spaces

    if (token.length() == 0) {
      // token empty: skip it (optional: you could report error)
      continue;
    }

    // 4) Map token to enum (to use switch later)
    CommandId id = parseCommand(token);

    // 5) Execute (handle) — can send response or execute action
    handleCommand(id, token);
  }

  // end: all tokens processed
}

//* Converts the token to a CommandId (case-insensitive)
uartFunctions::CommandId uartFunctions::parseCommand(const String &cmd) {
  String c = cmd;
  c.trim();
  c.toLowerCase(); // to compare in lowercase

  if (c == "chip_id") return CMD_CHIP_ID;
  if (c == "fw_version") return CMD_FW_VERSION;
  if (c == "bootloader_version") return CMD_BOOTLOADER_VERSION;
  if (c == "secure_session_on") return CMD_SECURE_SESSION_ON;
  if (c == "secure_session_off") return CMD_SECURE_SESSION_OFF;
  if (c.startsWith("encode_text")) return CMD_ENCODE_TEXT;
  return CMD_UNKNOWN;
}

//* Executes the corresponding action to th command
void uartFunctions::handleCommand(CommandId id, const String &originalCmd) {
  switch (id) {

    //? get chip ID
    case CMD_CHIP_ID: {
        // Call the function and send the response
        sendData(cmd_chip_id_func());
      break;
    }
        
    case CMD_FW_VERSION:
      sendData(cmd_fw_version_func());
      break;

    case CMD_BOOTLOADER_VERSION:
      sendData(cmd_bootloader_version_func());
      break;
      
    case CMD_SECURE_SESSION_ON:
      sendData(cmd_secure_session_func(true));
      break;

    case CMD_SECURE_SESSION_OFF:
      sendData(cmd_secure_session_func(false));
      break;

    case CMD_ENCODE_TEXT:
      char resultado[100];
      strcpy(resultado, originalCmd.c_str() + 12);
      sendData(resultado);
      sendData(String(strlen(resultado)));
      sendData(cmd_encode_text_func(resultado));
      break;

    default:
      // comando no reconocido
      sendData("ERR:UNKNOWN_COMMAND:" + originalCmd + "\n");
      break;
  }
}