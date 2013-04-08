#include <UART.h>
#include <digital_in.h>
#include <stdint.h>
#include <openlpc_xmodem.h>
#include <stm32f4xx.h>

#define STARTUP_ADDRESS 0x08000000
#define OFFSET_ADDRESS 0x1004 // (4Kb + endereço do Reset_Handler)

static uint32_t ticks;
void SysTick_Handler (void) {
	ticks++;
}

#define STRING "Aqui daria boot, mas por enquanto esta parado\n"

int main (void) {

    digital_io_t bl_mode;
    uart_t uart1;
    void (*start_addr)(void);
    uint8_t buff[2048];

    digitalin_setup (&bl_mode, GPIOA, 0);
    uart_setup (&uart1, USART1, 115200, 8, PARITY_NONE, 1);
    xmodem_startup_serial (&uart1);

    if (digitalin_read(&bl_mode)) {
        xmodem_recv (buff);
        uart_write (&uart1, buff, 2048);        
    }

    start_addr = (void (*)(void))(STARTUP_ADDRESS | OFFSET_ADDRESS);
   
//    start_addr();

    uart_write (&uart1, (uint8_t *)STRING, sizeof(STRING));

    while (1)
        ;

	return 0;
}

