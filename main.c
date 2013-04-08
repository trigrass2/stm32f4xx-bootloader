#include <UART.h>
#include <digital_in.h>
#include <stdint.h>
#include <openlpc_xmodem.h>

static uint32_t ticks;
void SysTick_Handler (void) {
	ticks++;
}

int main (void) {

	while (1)
		;

	return 0;
}

