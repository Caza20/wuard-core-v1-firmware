#include "commands/cmd_secure_session.hpp"

/**
 * @file cmd_chip_id_func.cpp
 * @author Wuard
 * @brief This function response the secure session to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

 session_state_t state = {0};

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_secure_session_func(bool flag) {
    String response = "";

    lt_ret_t ret;

    //* flag == true => establish secure session
    if (flag) {
        // Getting Certificate Store from TROPIC01
        uint8_t cert1[LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0}, cert2[LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0},
            cert3[LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0}, cert4[LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0};
        struct lt_cert_store_t store
            = {.certs = {cert1, cert2, cert3, cert4},
            .buf_len = {LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE, LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE,
                        LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE, LT_L2_GET_INFO_REQ_CERT_SIZE_SINGLE},
                .cert_len = {2040, 2040, 2040, 2040}};
        ret = lt_get_info_cert_store(&__lt_handle__, &store);
        if (LT_OK != ret) {
            // Failed to get Certificate Store , lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_GET_CERT_STORE;\n";
            return response;
        }

        // Get only stpub, we don't verify certificate chain here
        // Getting stpub key from Certificate Store 
        uint8_t stpub[32];
        ret = lt_get_st_pub(&store, stpub, 32);
        if (LT_OK != ret) {
            // Failed to get stpub key, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_GET_ST_PUB;\n";
            return response;    
        }

    //---------------------------------------------------------------------------------------//
        // Separated API calls for starting a secure session:
        // session_state_t state = {0};

        // Inicialize session from a server side by creating state->ehpriv and state->ehpub,
        // l2 request is prepared into handle's buffer (h->l2_buff)
        // Executing lt_out__session_start()...
        ret = lt_out__session_start(&__lt_handle__, PAIRING_KEY_SLOT_INDEX_0, &state);
        if (LT_OK != ret) {
            // lt_out__session_start() failed, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_START_SESSION;\n";
            return response;
        }

        // handle's buffer (h->l2_buff) now contains data which must be transferred over tunnel to TROPIC01

        // Following l2 functions are called on remote host
        //Executing lt_l2_send()..."
        ret = lt_l2_send(&__lt_handle__.l2);
        if (LT_OK != ret) {
            // lt_l2_send() failed, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_SEND_L2;\n";
            return response;
        }
        // Executing lt_l2_receive()..."
        ret = lt_l2_receive(&__lt_handle__.l2);
        if (LT_OK != ret) {
            // lt_l2_receive() failed, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_RECEIVE_L2;\n";
            return response;
        }

        // Handle's buffer (h->l2_buff) now contains data which must be transferred over tunnel back to the server

        // Once data are back on server's side, bytes are copied into h->l2_buff
        // Then following l2 function is called on server side
        // This function establishes gcm contexts for a session
        // Executing lt_in__session_start()...
        ret = lt_in__session_start(&__lt_handle__, stpub, PAIRING_KEY_SLOT_INDEX_0, sh0priv, sh0pub, &state);
        if (LT_OK != ret) {
            //lt_in__session_start failed, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_ESTABLISH_SESSION;\n";
            return response;
        }

        response = "OK:secure_session;\n";
    }

    //* flag == false => close secure session
    else {
        // Aborting Secure Session
        ret = lt_session_abort(&__lt_handle__);
        if (LT_OK != ret) {
            // Failed to abort Secure Session, lt_ret_verbose(ret)
            response = "ERR:FAILED_TO_ABORT_SESSION;\n";
            return response;
        }

        response = "OK:abort_session;\n";
    }

    
    return response;
}