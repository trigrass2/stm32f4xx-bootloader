/**
 * serial_io.c - Serial IO
 * Funções para escrita de texto e afins na serial
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include <stdarg.h>
#include <stdint.h>
#include <open_lpc.h>
#include <serial_io.h>

static uart_t *u_stdout, *u_stdin;

void serial_io_setup (uart_t *uart_stdout, uart_t *uart_stdin) {
	u_stdout = uart_stdout;
	u_stdin = uart_stdin;
}

static void print_int (int32_t val) {
	char num[11];
	int32_t i, j;

	if (val < 0)
		openlpc_putchar('-');

	val = (val < 0)?(-val):val;

	for (i = 0; i < 10; i++) {
		num[i] = '0' + (val % 10);
		val /= 10;
		if (val == 0)
			break;
	}

	for (j = i; j > -1; j--)
		openlpc_putchar (num[j]);

}

static void print_uint (uint32_t val) {
	char num[11];
	int32_t i, j;

	for (i = 0; i < 10; i++) {
		num[i] = '0' + (val % 10);
		val /= 10;
		if (val == 0)
			break;
	}

	for (j = i; j > -1; j--)
		openlpc_putchar (num[j]);
}

static void print_hex (uint32_t val) {
	char num[8];
	int32_t i, j;

	for (i = 0; i < 8; i++) {
		num[i] = val & 0x0F;
		val >>= 4;
		if (val == 0)
			break;
	}

	for (j = i; j > -1; j--) {
		if (num[j] < 0x0A)
			openlpc_putchar ('0' + num[j]);
		else
			openlpc_putchar ('A' + (num[j] - 0x0A));
	}
}

int32_t openlpc_printf (const char *fmt, ...) {

	int32_t i;
	char c;
	int32_t int_temp;
	uint32_t uint_temp;
	char char_temp;
	float float_temp;
	char * str_temp;
	va_list ap;

	va_start (ap, fmt);
	for (i = 0; fmt[i] != 0x00; i++) {
		if (fmt[i] != '%') {
			openlpc_putchar (fmt[i]);
		} else {
			i++;
			c = fmt[i];

			switch (c) {
				case 'd':
					int_temp = va_arg(ap, int32_t);
					print_int (int_temp);
					break;
				case 'u':
					uint_temp = va_arg(ap, uint32_t);
					print_uint (uint_temp);
					break;
				case 'c':
					char_temp = va_arg(ap, int);
					openlpc_putchar (char_temp);
					break;
				case 'x':
					uint_temp = va_arg(ap, uint32_t);
					print_hex (uint_temp);
					break;
				case 's':
					str_temp = va_arg(ap, char *);
					openlpc_puts (str_temp);
					break;
				case 'f':
					break;	// TODO: Impelemtar
				default:
					openlpc_putchar (c);
					break;
			}
		}
	}

	va_end(ap);
	return 0;
}

int32_t openlpc_puts (const char *s) {
	uint32_t i;
	for (i = 0; s[i] != 0x00; i++)
		;
	uart_write (u_stdout, (const uint8_t *)s, i);
	return 0;
}

int32_t openlpc_putchar (char c) {
	uart_write (u_stdout, (const uint8_t *)&c, 1);
	return 0;
}

