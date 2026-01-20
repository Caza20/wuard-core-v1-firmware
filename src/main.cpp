#include <Arduino.h>
#include "main.hpp"

uartFunctions uart;  // Create an instance of uartFunctions

Libtropic tropic;

// The Pico W LED is GPIO25, same for the regular Pico.
#define LED_PIN 25

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);

  uart.begin(UART_TX_PIN, UART_RX_PIN, UART_BAUDRATE, LT_UART_PORT);

  tropic.begin();

  // to have a moment to open the serial monitor
  delay(5000);

  uart.sendData("Hello from Raspberry Pi Pico with libtropic!\n");


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

