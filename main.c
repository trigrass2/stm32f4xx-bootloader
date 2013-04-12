#include <stdint.h>
#include <openlpc_xmodem.h>
#include <stm32f4xx.h>
#include <open_lpc.h>
#include <serial_io.h>
#include <openlpc_stdlib.h>
#include <ColoredOutput.h>

#define STARTUP_ADDRESS 0x08001000	// Desloca 4KB do Bootloader
#define OFFSET_ADDRESS 0x4 // (4 = endereço do Reset_Handler)

static uint32_t ticks;
void SysTick_Handler (void) {
	ticks++;
}

int main (void) {

    digital_io_t bl_mode;
    uart_t xmodem_uart, dbg;
    void (*start_addr)(void);
    uint8_t buff[2048];

    digitalin_setup (&bl_mode, GPIOA, 0);
    uart_setup (&xmodem_uart, USART1, 115200, 8, PARITY_NONE, 1);
	uart_setup (&dbg, USART2, 115200, 8, PARITY_NONE, 1);
    xmodem_startup_serial (&xmodem_uart);
	serial_io_setup (&dbg, &dbg);

    if (digitalin_read(&bl_mode)) {
		openlpc_puts (BOLD_CYAN("Recebendo por XMODEM...\r\n"));
        xmodem_recv (buff);
        uart_write (&dbg, buff, 2048);        
    }

	openlpc_puts (BOLD_YELLOW("Iniciando boot...\r\n"));

    start_addr = (void (*)(void))(STARTUP_ADDRESS | OFFSET_ADDRESS);
//    start_addr();

    while (1)
        ;

	return 0;
}

