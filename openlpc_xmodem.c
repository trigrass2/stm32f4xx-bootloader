/**
 * openlpc_xmodem.c
 * Implementação do protocolo XMODEM para ser utilizado pelo
 * OpenLPC
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include <stdint.h>
#include <openlpc_xmodem.h>
#include <open_lpc.h>
#include <stm32f4xx.h>

#define SOH 0x01	// Heading do XMODEM
#define EOT 0x04	// Fim da transmissão XMODEM
#define ACK 0x06	// Acknowledge
#define NAK 0x15	// Not acknowledge
#define CAN 0x18	// Cancel (deve ser enviado duas vezes)

typedef union {
	uint8_t raw_data[132];

	struct {	// Para ser usado com o XMODEM padrão
		uint8_t heading;
		uint8_t packet_number;
		uint8_t inv_packet_number;
		uint8_t payload[128];
		uint8_t checksum;
	} xmodem;
} xmodem_packet_t;

static uint8_t xmodem_calculate_checksum (const uint8_t *data, uint32_t size) {
    uint32_t checksum, i;

    for (i = 0, checksum = 0; i < size; checksum+=data[i++])
        ;

    return (uint8_t)(checksum & 0xFF);
}

static uart_t *local_uart;

void xmodem_startup_serial (uart_t *uart) {
    local_uart = uart;
}

int32_t xmodem_send (const void *data, uint32_t size) {

    return -1;
}

int32_t xmodem_recv (void *data) {

	uint8_t *d = (uint8_t *)data;
	uint8_t reply, last_pack_num = 0;
	xmodem_packet_t packet;
	uint32_t offset, i;
	int32_t data_offset = 0;

	// Iniciando a recepção
	reply = NAK;
	uart_write (local_uart, &reply, 1);

	while (1) {

		offset = 0;

		// Recebendo o pacote
		do {
			while (uart_data_available(local_uart) == 0) ;
			offset += uart_read (local_uart, &packet.raw_data[offset], sizeof(packet.raw_data) - offset);

			// Checa se houve pedido de cancelamento da conexão
			if (packet.raw_data[0] == CAN && packet.raw_data[1] == CAN) {
				data_offset = -1;
				break;
			}

			if (packet.raw_data[0] == EOT)
				goto END_RECEPTION;

		} while (offset < sizeof(packet.raw_data));
		
		// Inicia testes: se o protocolo é o XMODEM
		if (packet.xmodem.heading != SOH) 
			goto CANCEL_CONNECTION;

		// Testa o número do pacote
		if ( (packet.xmodem.packet_number ^ packet.xmodem.inv_packet_number) != 0xFF )
			goto REFUSE_PACKET;	// Se o checksum não bater

		// Valida número incremental do pacote
		if (last_pack_num != 0xFF && (packet.xmodem.packet_number < last_pack_num))
			goto REFUSE_PACKET;	// Se o número do pacote novo for menor que o recebido (exceto quando der o wrap-around

		// Testa o checksum do pacote
		if (packet.xmodem.checksum != xmodem_calculate_checksum(packet.raw_data, sizeof(packet) - 1))
			goto REFUSE_PACKET;

		for (i = 0; i < sizeof(packet.xmodem.payload); i++, data_offset++)
			d[data_offset] = packet.xmodem.payload[i];

		reply = ACK;
		uart_write (local_uart, &reply, 1);
		continue;

		REFUSE_PACKET:
		reply = NAK;
		uart_write (local_uart, &reply, 1);
		continue;

		CANCEL_CONNECTION:
		reply = CAN;
		uart_write (local_uart, &reply, 1);
		uart_write (local_uart, &reply, 1);
		data_offset = -1;
		break;
		
		END_RECEPTION:
		reply = ACK;
		uart_write (local_uart, &reply, 1);
		
		break;

	}

    return (data_offset & 0x7FFFFFFF);
}

