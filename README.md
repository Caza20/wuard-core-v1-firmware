# Wuard Core V1 – Firmware

Firmware for the **Wuard Core V1 PCB**, powered by an **RP2350 MCU** and the **Tropic01 cryptographic chip** by [Tropic Square](https://tropicsquare.com/).

![wuard-core-v1](https://github.com/wuard/Wuard-core-v1-pcb/blob/main/Output/images/wuard-core-v1-front.png)

**PCB repository:** [Wuard-Core-V1 PCB](https://github.com/wuard/Wuard-core-v1-pcb)

---

## Overview

Wuard Core V1 is a compact hardware platform that brings **HSM-like cryptographic capabilities** to any system through a simple UART interface.

The board combines two chips:

- **RP2350** (Raspberry Pi silicon) — handles communication and command processing
- **Tropic01** (Tropic Square) — a dedicated secure element that performs all cryptographic operations in hardware

This firmware acts as the bridge between them. It exposes the Tropic01's cryptographic features through a **plain-text UART protocol**, making it easy to integrate into any host system — microcontrollers, single-board computers, or desktop machines — regardless of language or platform.

---

## What it does

Once flashed, the board listens for text commands over UART and responds with structured results. No drivers, no SDK required on the host side — just a serial connection.

Available operations:

- **Device info** — chip ID, firmware version, bootloader version
- **Secure session** — establish or abort an encrypted L3 channel with the Tropic01
- **Random number generation** — hardware-backed true random values (up to 255 bytes)
- **Key management** — generate, read, and erase Ed25519 key pairs stored in 32 hardware slots
- **Digital signatures** — sign arbitrary messages using EdDSA (Ed25519) with a stored private key
- **Hashing** — SHA-256 hashing of any input message
- **Monotonic counters** — initialize, read, and increment tamper-resistant counters (16 slots)
- **Text encoding** — encode a message through the Tropic01

---

## UART Protocol

Commands are plain ASCII strings terminated with a semicolon (`;`). Multiple commands can be chained in a single transmission:

```
chip_id;fw_version;random_value_32bytes;
```

Responses follow a consistent format:

```
OK:<result>;       # on success
ERR:<description>; # on failure
```

Full command reference and usage examples are covered in the [API Reference](#) documentation.

---

## Dependencies

| Dependency | Source |
|---|---|
| `libtropic` (Arduino wrapper) | [Caza20/libtropic-platformio](https://github.com/Caza20/libtropic-platformio) `#develop` |
| `mbedTLS` | `baracodadailyhealthtech/mbedtls` (PlatformIO registry) |

---

## Build

This project uses [PlatformIO](https://platformio.org/) with the Arduino framework for RP2350.

### platformio.ini

```ini
[env:pico]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = pico
framework = arduino
board_build.core = earlephilhower

lib_deps =
    https://github.com/Caza20/libtropic-platformio.git#develop
    baracodadailyhealthtech/mbedtls

build_flags =
    -DLT_PLATFORM=rpi_pico
    -I include
    -D MBEDTLS_CONFIG_FILE=\"mbedtls_custom_config.h\"
    -D CMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY
```

### Key build flags

| Flag | Purpose |
|---|---|
| `-DLT_PLATFORM=rpi_pico` | Selects the Pico HAL in libtropic instead of the default Arduino HAL |
| `-D MBEDTLS_CONFIG_FILE=...` | Points mbedTLS to the project's stripped-down config for embedded use |
| `-D CMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY` | Prevents CMake from linking a shared-library test binary on a bare-metal target |

---

## Documentation

- **Getting Started** — hardware setup, flashing, and first connection *(coming soon)*
- **API Reference** — full command list with parameters and response formats *(coming soon)*

---

## Contributing

Pull requests are welcome. Feel free to submit bug fixes, improvements, or new features.

---

## 📜 License

MIT © [Wuard](https://wuard.io/)

---

<p align="center"><b>Wuard</b> · Wuard-Core-V1-firmware · 06/2026</p>