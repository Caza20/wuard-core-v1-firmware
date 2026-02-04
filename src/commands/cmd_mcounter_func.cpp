#include "commands/cmd_mcounter_func.hpp"

/**
 * @file cmd_mcounter_func.cpp
 * @author Wuard
 * @brief This function response the monotonic counter to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_mcounter_init_func(uint8_t index, uint32_t value) {
    String response = "";

    lt_ret_t ret;

    ret = tropic01.mcounterInit((lt_mcounter_index_t)index, value);
    if (ret != LT_OK) {
        // return "ERR:ENCODE;";
        return String("ERR:ENCODE;") + "code:" + String(ret) + ";";
    }

    // lt_ret_t ret = lt_out__mcounter_init(&__lt_handle__, (lt_mcounter_index_t)index, value);
    // if (ret != LT_OK) {
    //     // return "ERR:ENCODE;";
    //     return String("ERR:ENCODE;") + "code:" + String(ret) + ";";
    // }

    // // 2) Send to L2
    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // // 3) Receive from L2
    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // ret = lt_in__mcounter_init(&__lt_handle__);
    // if (ret != LT_OK) {
    //     // return "ERR:DECODE;";
    //     return String("ERR:DECODE;") + "code:" + String(ret) + ";";
    // }

    response = "OK:MCINIT;";

    return response;
}




String cmd_mcounter_get_func(uint8_t index) {
    String response = "";

    uint32_t value = 0;

    lt_ret_t ret;
    ret = tropic01.mcounterGet((lt_mcounter_index_t)index, &value);
    if (ret != LT_OK) {
        // return "ERR:ENCODE;";
        return String("ERR:ENCODE;") + "code:" + String(ret) + ";";
    }

    // lt_ret_t ret = lt_out__mcounter_get(&__lt_handle__, (lt_mcounter_index_t)index);
    // if (ret != LT_OK) {
    //     return "ERR:ENCODE;";
    // }

    // // 2) Send to L2
    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // // 3) Receive from L2
    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // ret = lt_in__mcounter_get(&__lt_handle__, &value);
    // if (ret != LT_OK) {
    //     return "ERR:DECODE;";
    // }

    response = "OK:MCGET:";
    response += String(value);
    response += ";";

    return response;
}



// Tropic decrement the monotic counters.

String cmd_mcounter_update_func(uint8_t index) {
    String response = "";

    lt_ret_t ret;
    ret = tropic01.mcounterUpdate((lt_mcounter_index_t)index);
    if (ret != LT_OK) {
        // return "ERR:ENCODE;";
        return String("ERR:ENCODE;") + "code:" + String(ret) + ";";
    }

    // lt_ret_t ret = lt_out__mcounter_update(&__lt_handle__, (lt_mcounter_index_t)index);
    // if (ret != LT_OK) {
    //     return "ERR:ENCODE;";
    // }

    // // 2) Send to L2
    // ret = lt_l2_send_encrypted_cmd(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:SEND;\n";
    // }

    // // 3) Receive from L2
    // ret = lt_l2_recv_encrypted_res(&__lt_handle__.l2, __lt_handle__.l3.buff, __lt_handle__.l3.buff_len);
    // if (ret != LT_OK) {
    //     return "ERR:RECV;\n";
    // }

    // ret = lt_in__mcounter_update(&__lt_handle__);
    // if (ret != LT_OK) {
    //     return "ERR:DECODE;";
    // }

    return "OK:MCUPDATE;";
}