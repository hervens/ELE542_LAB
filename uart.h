#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "globals.h"


/* UART Baud rate calculation */
#define UART_CPU               16000000UL   /* Crystal 16.000 Mhz */
#define UART_BAUD_RATE         9600         /* baud rate*/
#define UART_BAUD_SELECT       (UART_CPU/(UART_BAUD_RATE*16l)-1)

#define NORMAL_COMMAND        0xF1
#define FORCED_STOP           0xF0


/* Global functions */
extern void UART_SendByte         (uint8_t Data);
extern uint8_t  UART_ReceiveByte  (void);
extern void initUART             (void);


extern ROBOT robot;
#endif


