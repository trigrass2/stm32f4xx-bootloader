/**
 * openlpc_xmodem.h
 * Implementação do protocolo XMODEM para ser utilizado pelo
 * OpenLPC
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef OPENLPC_XMODEM_H
#define OPENLPC_XMODEM_H

#include <stdint.h>
#include <open_lpc.h>

void xmodem_startup_serial (uart_t *uart);

int32_t xmodem_send (const void *data, uint32_t size);

int32_t xmodem_recv (void *data);

#endif

