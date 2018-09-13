/*
 * console.c
 *
 * Created: 2018-09-13 16:43:45
 *  Author: Philip Ekholm
 */ 

#include <stdio_serial.h>
#include <asf.h>
#include <conf_board.h>

#include "config/conf_uart_serial.h"
#include "console_driver.h"

void console_init(void) {
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}