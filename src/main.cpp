#include <Arduino.h>
#include "main.hpp"

uartFunctions uart;  // Create an instance of uartFunctions

// ------------------------------------------ Other variables ------------------------------------------
// Used when initializing MbedTLS's PSA Crypto.
psa_status_t mbedtlsInitStatus;
// -----------------------------------------------------------------------------------------------------

// The Pico W LED is GPIO25, same for the regular Pico.
#define LED_PIN 25

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);
  

  uart.begin(UART_TX_PIN, UART_RX_PIN, UART_BAUDRATE, LT_UART_PORT);

  // to have a moment to open the serial monitor
  delay(5000);

  // Init MbedTLS's PSA Crypto.
  uart.sendData("Initializing MbedTLS PSA Crypto...");
  psa_status_t mbedtlsInitStatus = psa_crypto_init();
  if (mbedtlsInitStatus != PSA_SUCCESS) {
    uart.sendData("MbedTLS's PSA Crypto initialization failed, psa_status_t=");
    uart.sendData(String(mbedtlsInitStatus));
    cleanResourcesAndLoopForever();
  }
  uart.sendData("  OK");

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

