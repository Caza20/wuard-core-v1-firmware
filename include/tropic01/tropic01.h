#ifndef TROPIC01_H
#define TROPIC01_H

/**
 * @file tropic.h
 * @author Wuard
 * @brief This file is the TROPIC01 object.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <Arduino.h>
#include <LibtropicArduino.h>

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
extern Tropic01 tropic01;                              // TROPIC01 instance.
extern lt_ret_t returnVal;                            // Used for return values of Tropic01's methods.
extern char pingMsgToSend[100];                       // Ping message we will send to TROPIC01 via the Secure Channel.
extern char pingMsgToReceive[sizeof(pingMsgToSend)];  // Buffer for receiving the Ping message from TROPIC01.
// -----------------------------------------------------------------------------------------------------

// ---------------------------------------- Utility functions ------------------------------------------
void printLibtropicError(const char prefixMsg[], const lt_ret_t ret);
void cleanResourcesAndLoopForever(void);
// -----------------------------------------------------------------------------------------------------

#endif