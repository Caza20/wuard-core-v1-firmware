#include <Arduino.h>
#include "main.hpp"

uartFunctions uart;  // Create an instance of uartFunctions

// // -------------------------------------- TROPIC01 related macros --------------------------------------
// // GPIO pin definitions.
// #define TROPIC01_CS_PIN 5  // Platform's pin number where TROPIC01's SPI Chip Select pin is connected.
// #if LT_USE_INT_PIN
// #define TROPIC01_INT_PIN \
//     4  // Platform's pin number where TROPIC01's interrupt pin is connected.
//        // Is necessary only when -DLT_USE_INT_PIN=1 was set in build_flags.
// #endif

// // Pairing Key macros for establishing a Secure Channel Session with TROPIC01.
// // Using the default Pairing Key slot 0 of Production TROPIC01 chips.
// // #define PAIRING_KEY_PRIV sh0priv_prod0
// // #define PAIRING_KEY_PUB sh0pub_prod0
// #define PAIRING_KEY_PRIV sh0priv_eng_sample
// #define PAIRING_KEY_PUB sh0pub_eng_sample
// #define PAIRING_KEY_SLOT TR01_PAIRING_KEY_SLOT_INDEX_0
// // -----------------------------------------------------------------------------------------------------

// // ------------------------------------ TROPIC01 related variables -------------------------------------
// #if LT_SEPARATE_L3_BUFF
// // It is possible to define user's own buffer for L3 Layer data.
// // This is handy when using multiple instances of lt_handle_t - only one buffer for all instances will be used.
// uint8_t l3_buffer[LT_SIZE_OF_L3_BUFF] __attribute__((aligned(16))) = {0};
// #endif

// // Because Tropic01 constructor has different number of parameters depending on the used Libtropic
// // CMake options, we are wrapping its call with the directives, so this example is functional with
// // every supported Libtropic CMake option without making any changes to it.
// // This is of course not necessary in your application, if you are not frequently changing the
// // Libtropic CMake options that affect the Tropic01 constructor parameters.
// Tropic01 tropic01;                                             // TROPIC01 instance.
// lt_ret_t returnVal;                            // Used for return values of Tropic01's methods.
// char pingMsgToSend[] = "Hello World!";         // Ping message we will send to TROPIC01 via the Secure Channel.
// char pingMsgToReceive[sizeof(pingMsgToSend)];  // Buffer for receiving the Ping message from TROPIC01.
// // -----------------------------------------------------------------------------------------------------

// // ---------------------------------------- Utility functions ------------------------------------------
// // Helper function to save some source code lines when printing Libtropic errors using Serial.
// static void printLibtropicError(const char prefixMsg[], const lt_ret_t ret)
// {
//     uart.sendData(prefixMsg);
//     uart.sendData(String(ret));
//     uart.sendData(" (");
//     uart.sendData(lt_ret_verbose(ret));
//     uart.sendData(")");
// }

// static void cleanResourcesAndLoopForever(void)
// {
//     tropic01.end();             // Aborts all communication with TROPIC01 and frees resources.
//     // mbedtls_psa_crypto_free();  // Frees MbedTLS's PSA Crypto resources.
//     // SPI.end();                  // Deinitialize SPI.

//     while (true);
// }
// // -----------------------------------------------------------------------------------------------------

// The Pico W LED is GPIO25, same for the regular Pico.
#define LED_PIN 25

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);
  

  uart.begin(UART_TX_PIN, UART_RX_PIN, UART_BAUDRATE, LT_UART_PORT);

  // to have a moment to open the serial monitor
  delay(5000);

  tropic01.begin();
  // Init Tropic01 resources.
  uart.sendData("Initializing Tropic01 resources...");
  returnVal = tropic01.begin();
  if (returnVal != LT_OK) {
      printLibtropicError("  Tropic01.begin() failed, returnVal=", returnVal);
      cleanResourcesAndLoopForever();
  }
  uart.sendData("  OK");

      // Start Secure Channel Session with TROPIC01.
    uart.sendData("Starting Secure Channel Session with TROPIC01...");
    returnVal = tropic01.secureSessionStart(PAIRING_KEY_PRIV, PAIRING_KEY_PUB, PAIRING_KEY_SLOT);
    if (returnVal != LT_OK) {
        printLibtropicError("  Tropic01.secureSessionStart() failed, returnVal=", returnVal);
        cleanResourcesAndLoopForever();
    }
    uart.sendData("  OK");

    uart.sendData("---------------------------------------------------------------");
    uart.sendData(" ");
    uart.sendData("---------------------------- Loop -----------------------------");

  // to have a moment to open the serial monitor
  delay(5000);

  uart.sendData("Hello from Raspberry Pi Pico with libtropic!\n");

    uart.sendData("--");
    // Print our Ping message we want to send.
    uart.sendData("Sending the following Ping message to TROPIC01: \"");
    uart.sendData(pingMsgToSend);
    uart.sendData("\"");

    // Ping TROPIC01 with our message.
    returnVal = tropic01.ping(pingMsgToSend, pingMsgToReceive, sizeof(pingMsgToSend));
    if (returnVal != LT_OK) {
        printLibtropicError("  Tropic01.ping() failed, returnVal=", returnVal);
        cleanResourcesAndLoopForever();
    }
    uart.sendData("  OK");

    // Print received Ping message from TROPIC01.
    uart.sendData("Ping message received from TROPIC01: \"");
    uart.sendData(pingMsgToReceive);
    uart.sendData("\"");
   uart.sendData("--");
    uart.sendData(" ");

    // Wait some time before the next Ping.
    delay(2000);


}

void loop() {
    String cmd = uart.readData();
    if (cmd.length() > 0) {
        uart.sendData("Comand received: " + cmd + "\n");
        uart.processCommand(cmd);
        digitalWrite(LED_PIN, 1);
        delay(100); // only for testing
        digitalWrite(LED_PIN, 0);
        delay(500); // only for testing
    }
}

