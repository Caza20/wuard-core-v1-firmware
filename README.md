# Wuard Core V1 – Firmware

Firmware for the **Wuart Core V1 PCB**, powered by an **RP2350 MCU** and the **Tropic01 cryptographic chip** by [Tropic Square](https://tropicsquare.com/).

![wuard-core-v1](https://github.com/wuard/Wuard-core-v1-pcb/blob/main/Output/images/wuard-core-v1-front.png)

🔗 **PCB repository:**  
[Wuard-Core-V1 PCB](https://github.com/wuard/Wuard-core-v1-pcb)

---

## 📘 Overview

This repository contains the official firmware for the **Wuard Core V1** hardware platform.

The board integrates:

- **RP2350 MCU** (Raspberry Pi silicon)
- **Tropic01 Secure Element (Tropic Square)**

The firmware provides the **basic functionality of a standard Hardware Security Module (HSM)**.

Communication is performed through **USART**, where commands are sent as plain text strings.

---

## 📝 Command Structure

All commands **must end with a semicolon (`;`)**.  
This tells the firmware that the command is complete.

You can also send **multiple commands chained together**, separated by semicolons, to speed up processing:

```c
chip_id;fw_version;random_value_16bytes;
```

## ⚙️ Available Commands

Below is the full command list, including expected outputs and error behavior.

### Commands Index

- [1. chip_id](#1-chip_id)
- [2. fw_version](#2-fw_version)
- [3. bootloader_version](#3-bootloader_version)
- [4. secure_session_on](#4-secure_session_on)
- [5. secure_session_off](#5-secure_session_off)
- [6. encode_text_message](#6-encode_text_message)
- [7. random_value_Nbytes](#7-random_value_nbytes)
- [8. generate_key_slot](#8-generate_key_slot)
- [9. read_key_slot](#9-read_key_slot)
- [10. erase_key](#10-erase_key)
- [11. sign_message_slot_text](#11-sign_message_slot_text)
- [12. hash_sha256_message](#12-hash_sha256_message)
- [13. mcounter_init_index_value](#13-mcounter_init_index_value)
- [14. mcounter_get_index](#14-mcounter_get_index)
- [15. mcounter_update_index](#15-mcounter_update_index)


### 🔍 1. chip_id;

Returns full chip information and internal identifiers.

#### ✅ Success response:
```c
OK:chip_id:ver = 0x...: FL_PROD_DATA = 0x... :MAN_FUNC_TEST = 0x... :
Silicon rev = 0x... :Package ID = 0x... :Prov info ver = 0x... :
Fab ID = 0x... :P/N ID (short P/N) = 0x... :Prov date = 0x... :
HSM HW/FW/SW ver = 0x... :Programmer ver = 0x... :
S/N = 0x... :P/N (long) = 0x... :Prov template ver = 0x... :
Prov template tag = 0x... :Prov specification ver = 0x... :
Prov specification tag = 0x... :Batch ID = 0x...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🖥 2. fw_version;

Returns the firmware version for:

- RISC-V Application FW
- SPECT FW

#### ✅ Success:
```c
OK:RISC-V application FW version = ... :SPECT firmware version = ...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔧 3. bootloader_version;

Returns the bootloader version (available in v1.0.1 and v2.0.1).

#### ✅ Success:
```c
OK:Bootloader version = ...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔐 4. secure_session_on;

Enables a secure communication session (Layer L3) with the Tropic01.

#### ✅ Success:
```c
OK:secure_session;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔓 5. secure_session_off;

Aborts an active secure session.

#### ✅ Success:
```c
OK:abort_session;
```

#### ❌ Error:
```c
ERR:<description>;
```

### ✉️ 6. encode_text_message;

Encodes any following text. Example:
```c
encode_text_hello world;
```

#### ✅ Success:
```c
OK:TROPIC01:<encoded text>;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🎲 7. random_value_Nbytes;

Returns a random value of N bytes (max 255 bytes).
Example: 
```c
random_value_32bytes;
```

#### ✅ Success:
```c
OK:RANDOM_VALUE:<hex_value>;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔑 8. generate_key_slot;

Generates a key pair.
The private key is stored in the specified slot (0–31), and the public key is returned.

Example:
```c
generate_key_5;
```

#### ✅ Success:
```c
OK:KEY:0x...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 📖 9. read_key_slot;

Reads the public key stored in the given slot.

Example:
```c
read_key_3;
```

#### ✅ Success:
```c
OK:KEY:0x...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🧹 10. erase_key;

Erases the key stored in the specified slot.

Example:
```c
erase_key_7;
```

#### ✅ Success:
```c
OK:KEY_ERASED;
```

#### ❌ Error:
```c
ERR:<description>;
```

### ✍️ 11. sign_message_slot_text;

Signs a message using EdDSA with the private key stored in the chosen slot.

Example:
```c
sign_message_4_HelloWorld;
```

#### ✅ Success:
```c
OK:SIG:<hex_signature>;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🧮 12. hash_sha256_message;

Hashes a message using SHA-256.

Example:
```c
hash_sha256_HelloWorld;
```

#### ✅ Success:
```c
OK:hash:0x...;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔢 13. mcounter_init_index_value;

Initializes a monotonic counter at index 0–15, setting its value.

Example:
```c
mcounter_init_2_100;
```

#### ✅ Success:
```c
OK:MCINIT;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 📊 14. mcounter_get_index;

Reads the current value of a monotonic counter.

Example:
```c
mcounter_get_2;
```

#### ✅ Success:
```c
OK:MCGET:<value>;
```

#### ❌ Error:
```c
ERR:<description>;
```

### 🔼 15. mcounter_update_index;

Increments the monotonic counter at the given index.

Example:

```c
mcounter_update_2;
```

#### ✅ Success:
```c
OK:MCUPDATE;
```

#### ❌ Error:
```c
ERR:<description>;
```
------

## 🧰 Development Notes

Written in platformIO with C/C++ for RP2350.

USART text protocol designed to be simple and script-friendly.

Tropic01 communication handled through secure L3 interface when needed.

Suitable for HSM-like operations in embedded environments.

## 🤝 Contributing

Pull requests are welcome!
Feel free to submit improvements, translations, bug fixes or additional features.

## 📄 License

This project is released under the MIT License.
See LICENSE for details.

----

## Update

Last update at 12/2025.
