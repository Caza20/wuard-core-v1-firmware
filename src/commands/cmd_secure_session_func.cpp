#include "commands/cmd_secure_session_func.hpp"

/**
 * @file cmd_chip_id_func.cpp
 * @author Wuard
 * @brief This function response the secure session to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_secure_session_func(bool flag) {
    String response = "";

    if (flag) {
        lt_ret_t res = tropic01.secureSessionON(PAIRING_KEY_SLOT, PAIRING_KEY_PRIV, PAIRING_KEY_PUB);
        if (res != LT_OK) {
            response = "ERR:FAILED_TO_ESTABLISH_SESSION;\n";
            return response;
        }

        response = "OK:secure_session;\n";
    } else {
        lt_ret_t res = tropic01.secureSessionOFF();
        if (res != LT_OK) {
            response = "ERR:FAILED_TO_ABORT_SESSION;\n";
            return response;    
        }

        response = "OK:session_aborted;\n";
    }

    return response;

    // lt_ret_t ret;

    // //* flag == true => establish secure session
    // if (flag) {
    //     // Read certificate store
    //     uint8_t cert_ese[TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0};
    //     uint8_t cert_xxxx[TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0};
    //     uint8_t cert_tr01[TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0};
    //     uint8_t cert_root[TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE] = {0};

    //     struct lt_cert_store_t cert_store
    //         = { .certs = {cert_ese, cert_xxxx, cert_tr01, cert_root},
    //             .buf_len = {TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE, TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE,
    //                     TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE, TR01_L2_GET_INFO_REQ_CERT_SIZE_SINGLE},
    //             .cert_len = {0, 0, 0, 0}};
                

    //     ret = lt_get_info_cert_store(handle, &cert_store);
    //     if (LT_OK != ret) {
    //         // Failed to get Certificate Store , lt_ret_verbose(ret)
    //         response = "ERR:FAILED_TO_GET_CERT_STORE;\n";
    //         return response;
    //     }

    //     // Extract STPub
    //     uint8_t stpub[TR01_STPUB_LEN] = {0};
    //     ret = lt_get_st_pub(&cert_store, stpub);
    //     if (LT_OK != ret) {
    //         // Failed to get stpub key, lt_ret_verbose(ret)
    //         response = "ERR:FAILED_TO_GET_ST_PUB;\n";
    //         return response;    
    //     }

    // //---------------------------------------------------------------------------------------//
    //     // // Separated API calls for starting a secure session:
    //     // // session_state_t state = {0};

    //     // // Inicialize session from a server side by creating state->ehpriv and state->ehpub,
    //     // // l2 request is prepared into handle's buffer (h->l2_buff)
    //     // // Executing lt_out__session_start()...
    //     // ret = lt_out__session_start(&__lt_handle__, PAIRING_KEY_SLOT_INDEX_0, &state);
    //     // if (LT_OK != ret) {
    //     //     // lt_out__session_start() failed, lt_ret_verbose(ret)
    //     //     response = "ERR:FAILED_TO_START_SESSION;\n";
    //     //     return response;
    //     // }

    //     // // handle's buffer (h->l2_buff) now contains data which must be transferred over tunnel to TROPIC01

    //     // // Following l2 functions are called on remote host
    //     // //Executing lt_l2_send()..."
    //     // ret = lt_l2_send(&__lt_handle__.l2);
    //     // if (LT_OK != ret) {
    //     //     // lt_l2_send() failed, lt_ret_verbose(ret)
    //     //     response = "ERR:FAILED_TO_SEND_L2;\n";
    //     //     return response;
    //     // }
    //     // // Executing lt_l2_receive()..."
    //     // ret = lt_l2_receive(&__lt_handle__.l2);
    //     // if (LT_OK != ret) {
    //     //     // lt_l2_receive() failed, lt_ret_verbose(ret)
    //     //     response = "ERR:FAILED_TO_RECEIVE_L2;\n";
    //     //     return response;
    //     // }

    //     // // Handle's buffer (h->l2_buff) now contains data which must be transferred over tunnel back to the server

    //     // // Once data are back on server's side, bytes are copied into h->l2_buff
    //     // // Then following l2 function is called on server side
    //     // // This function establishes gcm contexts for a session
    //     // // Executing lt_in__session_start()...
    //     // ret = lt_in__session_start(&__lt_handle__, stpub, PAIRING_KEY_SLOT_INDEX_0, sh0priv, sh0pub, &state);
    //     // if (LT_OK != ret) {
    //     //     //lt_in__session_start failed, lt_ret_verbose(ret)
    //     //     response = "ERR:FAILED_TO_ESTABLISH_SESSION;\n";
    //     //     return response;
    //     // }

    //     ret = lt_session_start(handle, stpub, pkey_index, shipriv, shipub);
    //     if (ret != LT_OK) {
    //         response = "ERR:FAILED_TO_ESTABLISH_SESSION;\n";
    //         return response;
    //     }

    //     response = "OK:secure_session;\n";
    // }

    // //* flag == false => close secure session
    // else {
    //     // Aborting Secure Session
    //     ret = lt_session_abort(handle);
    //     if (LT_OK != ret) {
    //         // Failed to abort Secure Session, lt_ret_verbose(ret)
    //         response = "ERR:FAILED_TO_ABORT_SESSION;\n";
    //         return response;
    //     }

    //     response = "OK:abort_session;\n";
    // }

    
    // return response;
}