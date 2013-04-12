/**
 * serial_io.h - Serial IO
 * Funções para escrita de texto e afins na serial
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include <stdint.h>
#include <open_lpc.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t openlpc_printf (const char *fmt, ...);
int32_t openlpc_puts (const char *s);
int32_t openlpc_putchar (char c);

void serial_io_setup (uart_t *uart_stdout, uart_t *uart_stdin);

#ifdef __cplusplus
}
#endif

#endif

