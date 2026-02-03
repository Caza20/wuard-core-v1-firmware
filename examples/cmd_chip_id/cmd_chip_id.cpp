#include <Arduino.h>
#include <LibtropicArduino.h>

#include "commands/cmd_chip_id_func.hpp"

// -------------------------------------- TROPIC01 related macros --------------------------------------
// GPIO pin definitions.
#define TROPIC01_CS_PIN 5  // Platform's pin number where TROPIC01's SPI Chip Select pin is connected.
#if LT_USE_INT_PIN
#define TROPIC01_INT_PIN \
    4  // Platform's pin number where TROPIC01's interrupt pin is connected.
       // Is necessary only when -DLT_USE_INT_PIN=1 was set in build_flags.
#endif

// Pairing Key macros for establishing a Secure Channel Session with TROPIC01.
// Using the default Pairing Key slot 0 of Production TROPIC01 chips.
// #define PAIRING_KEY_PRIV sh0priv_prod0
// #define PAIRING_KEY_PUB sh0pub_prod0
#define PAIRING_KEY_PRIV sh0priv_eng_sample
#define PAIRING_KEY_PUB sh0pub_eng_sample
#define PAIRING_KEY_SLOT TR01_PAIRING_KEY_SLOT_INDEX_0
// -----------------------------------------------------------------------------------------------------

// ------------------------------------ TROPIC01 related variables -------------------------------------
#if LT_SEPARATE_L3_BUFF
// It is possible to define user's own buffer for L3 Layer data.
// This is handy when using multiple instances of lt_handle_t - only one buffer for all instances will be used.
uint8_t l3_buffer[LT_SIZE_OF_L3_BUFF] __attribute__((aligned(16))) = {0};
#endif

// Because Tropic01 constructor has different number of parameters depending on the used Libtropic
// CMake options, we are wrapping its call with the directives, so this example is functional with
// every supported Libtropic CMake option without making any changes to it.
// This is of course not necessary in your application, if you are not frequently changing the
// Libtropic CMake options that affect the Tropic01 constructor parameters.
Tropic01 tropic01;                                             // TROPIC01 instance.
lt_ret_t returnVal;                            // Used for return values of Tropic01's methods.
// -----------------------------------------------------------------------------------------------------

// ---------------------------------------- Utility functions ------------------------------------------
// Helper function to save some source code lines when printing Libtropic errors using Serial.
static void printLibtropicError(const char prefixMsg[], const lt_ret_t ret)
{
    Serial.println(prefixMsg);
    Serial.println(String(ret));
    Serial.println(" (");
    Serial.println(lt_ret_verbose(ret));
    Serial.println(")");
}

static void cleanResourcesAndLoopForever(void)
{
    tropic01.end();             // Aborts all communication with TROPIC01 and frees resources.
    // mbedtls_psa_crypto_free();  // Frees MbedTLS's PSA Crypto resources.
    // SPI.end();                  // Deinitialize SPI.

    while (true);
}
// -----------------------------------------------------------------------------------------------------

// The Pico W LED is GPIO25, same for the regular Pico.
#define LED_PIN 25

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);

  // to have a moment to open the serial monitor
  delay(5000);

  tropic01.begin();
  // Init Tropic01 resources.
  Serial.println("Initializing Tropic01 resources...");
  returnVal = tropic01.begin();
  if (returnVal != LT_OK) {
      printLibtropicError("  Tropic01.begin() failed, returnVal=", returnVal);
      cleanResourcesAndLoopForever();
  }
  Serial.println("  OK");

      // Start Secure Channel Session with TROPIC01.
    Serial.println("Starting Secure Channel Session with TROPIC01...");
    returnVal = tropic01.secureSessionStart(PAIRING_KEY_PRIV, PAIRING_KEY_PUB, PAIRING_KEY_SLOT);
    if (returnVal != LT_OK) {
        printLibtropicError("  Tropic01.secureSessionStart() failed, returnVal=", returnVal);
        cleanResourcesAndLoopForever();
    }
    Serial.println("  OK");

    Serial.println("---------------------------------------------------------------");
    Serial.println(" ");
    Serial.println("---------------------------- Loop -----------------------------");

  // to have a moment to open the serial monitor
  delay(5000);

    lt_chip_id_t chip_id = {0};
    tropic01.getChipID(chip_id);
    // Call the function and send the response
    Serial.println(cmd_chip_id_func(chip_id));

    // Wait some time before the next Ping.
    delay(2000);


}

void loop() {

}