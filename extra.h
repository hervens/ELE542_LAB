#include <stdio.h>
#include <stdlib.h>

FILE uart_output = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
/*
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
FILE uart_io FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void uart_putchar(char c, FILE *stream) {
  if (c == '\n') {
    uart_putchar('\r', stream);
  }
  loop_until_bit_is_set(UCSRA, UDRE);
  UDR = c;
}

char uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSRA, RXC); 
  return UDR;
}


void uart_putchar2(char c) {
  loop_until_bit_is_set(UCSRA, UDRE); 
  UDR = c;
}
char uart_getchar2(void) {
  loop_until_bit_is_set(UCSRA, RXC); 
  return UDR;
}
int uart_putchar3(char c)
{
  if (c == ’\n’)
    uart_putchar(’\r’);
  loop_until_bit_is_set(USR, UDRE);
  UDR = c;
  return 0; 
}

void debug_P(const char *addr)
{
  char c;
  c=0xFE;
  while ((c = pgm_read_byte(addr++)))
    uart_putchar3(c);
  c=0xFF;
}

*/

void usart_putchar(char data) {
      // Wait for empty transmit buffer
           while ( !(UCSRA & (_BV(UDRE))) );// Start transmission
                   UDR = data; 
}

int usart_putchar_printf(char var, FILE *stream) {
      static char start = 0xFE;
      static char end   = 0xFF;
      // translate \n to \r for br@y++ terminal
           if (var == '\n') 
             usart_putchar('\r');
           
           usart_putchar(start) 
           usart_putchar(var);
           usart_putchar(end);
                   return 0;
             }
