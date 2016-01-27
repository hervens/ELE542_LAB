#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <var/io.h>

void send_debug(char *msg, short size)
{
	UART_SendByte(0xFE);
	int i;

	for(i = 0; i<size; i++)
	{
		UART_SendByte(msg[i]);
	}
	UART_SendByte(0xFF);

}
void send_debug_int(int c)
{
	UART_SendByte(0xFE);
	UART_SendByte(c);
	UART_SendByte(0xFF);

}

void send_debugu08(u08 data)
{
	UART_SendByte(0xFE);
	UART_SendByte(data);
	UART_SendByte(0xFF);

}
void UART_SendByte(unint8t_ u8Data)
{


}
void UART_Init(void)
{

UCSRC=((1<<URSEL)| (0<<UMSEL)| (0<<UPM1)|(0<<UPM0)|(0<<USBS)| (1<<UCSZ1) | (1<<UCSZ1) | (0<<UCPOL));


UCSRB=((1<<RXCIE)|(1<<TXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2));

UBRRH=(uint8_t)(UART_BAUD_SELECT<<8);

UBRRL=((uint8_t)(UART_BAUD_SELECT & 0x00FF);

}
