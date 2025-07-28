<img width="970" height="728" alt="image" src="https://github.com/user-attachments/assets/ced1cfee-1151-4be4-899f-413d5c9c2a51" />

# VCP-Display: Dual-Core STM32 + Desktop Visualization System

A desktop based system for emulating an embedded display, with fully containerized development environments for both firmware and host-side applications. The goal is to provide embedded developers a way to test their embedded graphics (e.g., VHDL code) without committing to a specific display.

---

## Project Overview

This system includes:

- **Embedded firmware** for STM32H7 (CM4 + CM7) using CMSIS and HAL libraries.
- **Desktop applications** in C++ for communication and data visualization (embedded display emulation).
- **Containerized development environments** (via Docker and VSCode DevContainers).
- **High-throughput data streaming** over USB Virtual COM Port (CDC-UART) for real-time analysis (> 700 KB/s).

---

## Key Features

- **Dual-core firmware architecture** (CM4 for control, CM7 for compute).
- **Middleware support**: CMSIS-DSP, CMSIS-NN, CMSIS-RTOS2.
- **USB VCP communication layer** for fast data transfer.
- **Modular desktop apps** for display, communication, and test automation.
- **DevContainers** for reproducible environments.

---

## Project Structure

<details>
<summary><strong>📁 Embedded</strong></summary>

- `CM4/` – Application code for Cortex-M4 (DMA, syscalls, main loop)
- `CM7/` – Application code for Cortex-M7 (USART)
- `Common/` – Shared startup & dual-core boot code
- `Drivers/` – CMSIS, HAL, DSP, NN, RTOS2 middleware
- `Makefile/` – Build scripts for CM4, CM7
- `PyListen/` – Python scripts to parse UART output and validate firmware results

</details>

<details>
<summary><strong>📁 Desktop</strong></summary>

- `Comm/` – C++ service to read, decode, and forward serial data
- `Display/` – C++ GUI application to visualize streamed data

</details>

---

## Build & Run

### 📦 Dev Environment

Ensure [Docker](https://www.docker.com/) and [VSCode](https://code.visualstudio.com/) are installed.

📝 License
MIT License

👤 Authors
Developed and maintained by @fadi-eid
