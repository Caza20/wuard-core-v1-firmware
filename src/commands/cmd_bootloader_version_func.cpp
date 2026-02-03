#include "commands/cmd_bootloader_version_func.hpp"

/**
 * @file cmd_bootloader_version_func.cpp
 * @author Wuard
 * @brief This function response the bootloader version to send by uart.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */

//**********************************************************************
//*                     Principal functions                            *
//**********************************************************************

String cmd_bootloader_version_func() {
    // String response = "";

    // uint8_t fw_ver[TR01_L2_GET_INFO_RISCV_FW_SIZE] = {0};

    // lt_ret_t ret = lt_reboot(handle, TR01_MAINTENANCE_REBOOT);
    // if (ret != LT_OK) {
    //     lt_deinit(handle);
    //     response = "ERR:REBOOT_FAIL;\n";
    // }

    // lt_tr01_mode_t mode = LT_TR01_MAINTENANCE;

    // ret = lt_get_tr01_mode(handle, &mode);
    // if (ret == LT_OK) {
    //     ret = lt_get_info_riscv_fw_ver(handle, fw_ver);
    //     if (ret != LT_OK) {
    //         lt_deinit(handle);
    //         response = "ERR:GET_FW_VERSION_FAIL;\n";
    //     }
    // } else {
    //     lt_deinit(handle);
    //     response = "ERR:GET_MODE_FAIL;\n";
    // }

    // // Checking if bootloader version is 1.0.1
    // if (((fw_ver[3] & 0x7f) == 1) && (fw_ver[2] == 0) && (fw_ver[1] == 1) && (fw_ver[0] == 0)) {
    //     char buff_2X[3]; 
    //     sprintf(buff_2X, "%02X", fw_ver[3] & 0x7f); 
    //     String fw_ver_3 = String(buff_2X);
    //     sprintf(buff_2X, "%02X", fw_ver[2]); 
    //     String fw_ver_2 = String(buff_2X);
    //     sprintf(buff_2X, "%02X", fw_ver[1]); 
    //     String fw_ver_1 = String(buff_2X);
    //     sprintf(buff_2X, "%02X", fw_ver[0]); 
    //     String fw_ver_0 = String(buff_2X);

    //     response = "OK:Bootloader version = " + fw_ver_3 + "." + fw_ver_2 + "." + fw_ver_1 + " (+ ." + fw_ver_0 + ")";

    //     response += get_headers_v1(handle);
    // }
    // else {
    //     // Checking if bootloader version is 2.0.1
    //     if (((fw_ver[3] & 0x7f) == 2) && (fw_ver[2] == 0) && (fw_ver[1] == 1) && (fw_ver[0] == 0)) {
    //         char buff_2X[3]; 
    //         sprintf(buff_2X, "%02X", fw_ver[3] & 0x7f); 
    //         String fw_ver_3 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[2]); 
    //         String fw_ver_2 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[1]); 
    //         String fw_ver_1 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[0]); 
    //         String fw_ver_0 = String(buff_2X);

    //         response = "OK:Bootloader version = " + fw_ver_3 + "." + fw_ver_2 + "." + fw_ver_1 + " (+ ." + fw_ver_0 + ")";

    //         response += get_headers_v2(handle);
    //     }
    //     else {
    //         char buff_2X[3]; 
    //         sprintf(buff_2X, "%02X", fw_ver[3] & 0x7f); 
    //         String fw_ver_3 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[2]); 
    //         String fw_ver_2 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[1]); 
    //         String fw_ver_1 = String(buff_2X);
    //         sprintf(buff_2X, "%02X", fw_ver[0]); 
    //         String fw_ver_0 = String(buff_2X);

    //         response = "ERR:UNKNOWN_BOOTLOADER_VERSION=" + fw_ver_3 + "." + fw_ver_2 + "." + fw_ver_1 + " (+ ." + fw_ver_0 + ");\n";

    //         return response;
    //     }
    // }
    
    // return response + ";\n";

    String response = "";

    uint8_t fw_ver[TR01_L2_GET_INFO_RISCV_FW_SIZE] = {0};

    lt_ret_t res = tropic01.getBootloaderVersion(fw_ver);
    if (res != LT_OK) {
      response = "ERR:FW_VERSION_FAIL;\n";
      return response;
    }

    response = tropic01.printBootloaderVersion(fw_ver);

    return response;
}

// // //**********************************************************************
// // //*                     Auxiliary functions                            *
// // //**********************************************************************

// String get_headers_v1(lt_handle_t* handle) {
//     String response = "";

//     uint8_t header[TR01_L2_GET_INFO_FW_HEADER_SIZE] = {0};
//     uint16_t header_read_size = 0;

//     // Read header from FW_BANK_FW1
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_FW1, header, sizeof(header), &header_read_size) == LT_OK) {
//         response = header_boot_v1_0_1(header, TR01_FW_BANK_FW1);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_FW_BANK1;\n";
//         return response;
//     }

//     // Read header from FW_BANK_FW2
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_FW2, header, sizeof(header), &header_read_size) == LT_OK) {
//         response += header_boot_v1_0_1(header, TR01_FW_BANK_FW2);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_FW_BANK2;\n";
//         return response;
//     }

//     // Read header from FW_BANK_SPECT1
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_SPECT1, header, sizeof(header), &header_read_size) == LT_OK) {
//         response += header_boot_v1_0_1(header, TR01_FW_BANK_SPECT1);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_SPECT_BANK1;\n";
//         return response;
//     }

//     // Read header from FW_BANK_SPECT2
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_SPECT2, header, sizeof(header), &header_read_size) == LT_OK) {
//         response += header_boot_v1_0_1(header, TR01_FW_BANK_SPECT2);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_SPECT_BANK2;\n";
//         return response;
//     }

//     return response;
// }

// String header_boot_v1_0_1(uint8_t *data, lt_bank_id_t bank_id) {
//     String response = "";

//     struct lt_header_boot_v1_t *p_h = (struct lt_header_boot_v1_t *)data;
    
//     switch (bank_id) {
//         case TR01_FW_BANK_FW1:
//             response ="Firmware bank 1 header=";
//             break;
//         case TR01_FW_BANK_FW2:
//             response ="Firmware bank 2 header=";
//             break;
//         case TR01_FW_BANK_SPECT1:
//             response = "SPECT bank 1 header=";
//             break;
//         case TR01_FW_BANK_SPECT2:
//             response = "SPECT bank 2 header=";
//             break;
//         default:
//             response = "Unknown bank ID=" + (int)bank_id;
//             return response;
//     }

//     char buff_2X[3]; 
//     sprintf(buff_2X, "%02X", p_h->type[3]); 
//     String ph_type_3 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->type[2]); 
//     String ph_type_2 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->type[1]); 
//     String ph_type_1 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->type[0]); 
//     String ph_type_0 = String(buff_2X);

//     response += "Type= " + ph_type_3 + ph_type_2 + ph_type_1 + ph_type_3 + ":";

//     sprintf(buff_2X, "%02X", p_h->version[3]); 
//     String ph_version_3 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->version[2]); 
//     String ph_version_2 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->version[1]); 
//     String ph_version_1 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->version[0]); 
//     String ph_version_0 = String(buff_2X);

//     response += "Version= " + ph_version_3 + ph_version_2 + ph_version_1 + ph_version_0 + ":";

//     sprintf(buff_2X, "%02X", p_h->size[3]); 
//     String ph_size_3 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->size[2]); 
//     String ph_size_2 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->size[1]); 
//     String ph_size_1 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->size[0]); 
//     String ph_size_0 = String(buff_2X);

//     response += "Size= " + ph_size_3 + ph_size_2 + ph_size_1 + ph_size_0 + ":";

//     sprintf(buff_2X, "%02X", p_h->git_hash[3]); 
//     String ph_git_hash_3 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->git_hash[2]); 
//     String ph_git_hash_2 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->git_hash[1]); 
//     String ph_git_hash_1 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->git_hash[0]); 
//     String ph_git_hash_0 = String(buff_2X);

//     response += "Git hash= " + ph_git_hash_3 + ph_git_hash_2 + ph_git_hash_1 + ph_git_hash_0 + ":";

//     sprintf(buff_2X, "%02X", p_h->hash[3]); 
//     String ph_hash_3 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->hash[2]); 
//     String ph_hash_2 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->hash[1]); 
//     String ph_hash_1 = String(buff_2X);
//     sprintf(buff_2X, "%02X", p_h->hash[0]); 
//     String ph_hash_0 = String(buff_2X);

//     response += "FW hash= " + ph_hash_3 + ph_hash_2 + ph_hash_1 + ph_hash_0 + ":";

//     return response;
// }

// // ----------------------------

// String get_headers_v2(lt_handle_t* handle) {
//     String response = "";

//     uint8_t header[TR01_L2_GET_INFO_FW_HEADER_SIZE] = {0};
//     uint16_t header_read_size = 0;

//     // Read header from FW_BANK_FW1
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_FW1, header, sizeof(header), &header_read_size) == LT_OK) {
//         header_boot_v2_0_1(header, TR01_FW_BANK_FW1);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_FW_BANK_1;";
//         return response;
//     }

//     // Read header from FW_BANK_FW2
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_FW2, header, sizeof(header), &header_read_size) == LT_OK) {
//         header_boot_v2_0_1(header, TR01_FW_BANK_FW2);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_FW_BANK_2;";
//         return response;
//     }

//     // Read header from FW_BANK_SPECT1
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_SPECT1, header, sizeof(header), &header_read_size) == LT_OK) {
//         header_boot_v2_0_1(header, TR01_FW_BANK_SPECT1);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_SPECT_BANK_1;";
//         return response;
//     }

//     // Read header from FW_BANK_SPECT2
//     memset(header, 0, sizeof(header));
//     if (lt_get_info_fw_bank(handle, TR01_FW_BANK_SPECT2, header, sizeof(header), &header_read_size) == LT_OK) {
//         header_boot_v2_0_1(header, TR01_FW_BANK_SPECT2);
//     }
//     else {
//         response = "ERR:FAILED_TO_GET_SPECT_BANK_2;";
//         return response;
//     }

//     return response;
// }

// // This function prints the header in the new format used in bootloader version 2.0.1
// String header_boot_v2_0_1(uint8_t *data, lt_bank_id_t bank_id)
// {
//     String response = "";

//     struct lt_header_boot_v2_t *p_h = (struct lt_header_boot_v2_t *)data;

//     switch (bank_id) {
//         case TR01_FW_BANK_FW1:
//             response = "Firmware bank 1 header=";
//             break;
//         case TR01_FW_BANK_FW2:
//             response = "Firmware bank 2 header=";
//             break;
//         case TR01_FW_BANK_SPECT1:
//             response = "SPECT bank 1 header=";
//             break;
//         case TR01_FW_BANK_SPECT2:
//             response = "SPECT bank 2 header=";
//             break;
//         default:
//             response = "Unknown bank ID " + String((int)bank_id) + ";";
//             return response;
//     }

//     char buff_4X[5]; 
//     sprintf(buff_4X, "%04X", p_h->type); 
//     String ph_type = String(buff_4X);

//     response += "Type= " + ph_type + ":";

//     char buff_2X[3]; 
//     sprintf(buff_2X, "%02X", p_h->padding); 
//     String ph_padding = String(buff_2X);

//     response += "Padding= " + ph_padding + ":";

//     sprintf(buff_2X, "%02X", p_h->header_version); 
//     String ph_header_version = String(buff_2X);

//     response += "FW header version= " + ph_header_version + ":\n";

//     char buff_8X[9]; 
//     sprintf(buff_8X, "%08X", p_h->ver); 
//     String ph_ver = String(buff_8X);

//     response += "Version= " + ph_ver + ":";

//     sprintf(buff_8X, "%08X", p_h->size); 
//     String ph_size = String(buff_8X);

//     response += "Size= " + ph_size + ":";

//     sprintf(buff_8X, "%08X", p_h->git_hash); 
//     String ph_git_hash = String(buff_8X);

//     response += "Git hash= " + ph_git_hash + ":";

//     // Hash str has 32B
//     char hash_str[32 * 2 + 1] = {0};
//     for (int i = 0; i < 32; i++) {
//         snprintf(hash_str + i * 2, sizeof(hash_str) - i * 2, "%02" PRIX8 "", p_h->hash[i]);
//     }
    
//     response += "Hash=" + String(hash_str) + ":";
//     response +="Pair version=" + String(p_h->pair_version) + ":";

//     return response;
// }