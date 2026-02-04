#include "tropic01/tropic01.h"

Tropic01 tropic01; 

lt_ret_t returnVal;                            // Used for return values of Tropic01's methods.
char pingMsgToSend[] = "Hello World!";         // Ping message we will send to TROPIC01 via the Secure Channel.
char pingMsgToReceive[sizeof(pingMsgToSend)];  // Buffer for receiving the Ping message from TROPIC01.

// ---------------------------------------- Utility functions ------------------------------------------
// Helper function to save some source code lines when printing Libtropic errors using Serial.
void printLibtropicError(const char prefixMsg[], const lt_ret_t ret)
{
    Serial.println(prefixMsg);
    Serial.println(String(ret));
    Serial.println(" (");
    Serial.println(lt_ret_verbose(ret));
    Serial.println(")");
}

void cleanResourcesAndLoopForever(void)
{
    tropic01.end();             // Aborts all communication with TROPIC01 and frees resources.
    // mbedtls_psa_crypto_free();  // Frees MbedTLS's PSA Crypto resources.
    // SPI.end();                  // Deinitialize SPI.

    while (true);
}
// -----------------------------------------------------------------------------------------------------