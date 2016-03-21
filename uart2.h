#ifndef __UART2_H__
#define __UART2_H__

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <avr/pgmspace.h>
#include "globals.h"
#define outp(val,port) port = val
#define inp(port) port

#define NORMAL_COMMAND        0xF1
#define FORCED_STOP           0xF0

extern Robot robot;

/* Global definitions */
typedef unsigned char  u08;
typedef          char  s08;
typedef unsigned short u16;
typedef          short s16;

/* UART Baud rate calculation */
#define UART_CPU               16000000UL   /* Crystal 16.000 Mhz */
#define UART_BAUD_RATE         9600         /* baud rate*/
#define UART_BAUD_SELECT       (UART_CPU/(UART_BAUD_RATE*16l)-1)

/* Global functions */
extern void UART_SendByte       (u08 Data);
extern u08  UART_ReceiveByte    (void);
extern void UART_PrintfProgStr  (PGM_P pBuf);
extern void UART_PrintfEndOfLine(void);
extern void UART_Printfu08      (u08 Data);
extern void UART_Printfu16      (u16 Data);
extern void initUART           (void);
extern void send_debug(char *msg, short size);
extern void send_debug_int(int c);
extern void send_debug08(u08 data);

/* Macros */
#define PRINT(string) (UART_PrintfProgStr((PGM_P) string))
#define EOL           UART_PrintfEndOfLine
#endif


