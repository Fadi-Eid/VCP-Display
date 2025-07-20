# Run with "sudo bash flash_cm7.sh"
openocd -f interface/stlink.cfg -f target/stm32h7x_dual_bank.cfg -c "program ./build/STM32H755-UART-VCP_CM4.elf verify reset exit"