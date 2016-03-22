#include <stdio.h>
#include <stdlib.h>

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
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
  loop_until_bit_is_set(UCSRA, RXC); /* Wait until data exists. */
  return UDR;
}

/*
 *
 *
 */
void uart_putchar2(char c) {
  loop_until_bit_is_set(UCSRA, UDRE); /* Wait until data register empty. */
  UDR = c;
}
char uart_getchar2(void) {
  loop_until_bit_is_set(UCSRA, RXC); /* Wait until data exists. */
  return UDR;
}
/*
 *
 *
 */
int uart_putchar3(char c)
{
  if (c == ’\n’)
    uart_putchar(’\r’);
  loop_until_bit_is_set(USR, UDRE);
  UDR = c;
  return 0; /* so it could be used for fdevopen(), too */
}

void debug_P(const char *addr)
{
  char c;
  c=0xFE;
  while ((c = pgm_read_byte(addr++)))
    uart_putchar3(c);
  c=0xFF;
}

