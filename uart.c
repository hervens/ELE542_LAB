#include "uart.h"


/* UART global variables */
volatile uint8_t   UART_Ready;
volatile uint8_t   UART_ReceivedChar;
         uint8_t   UART_RxChar;
         uint8_t*  pUART_Buffer;
uint8_t state=0;

/* UART Transmit Complete Interrupt Function */
SIGNAL(SIG_UART_TRANS)      
{
    /* Test if a string is being sent */
    if (pUART_Buffer!=0)
    {
        /* Go to next character in string */
        pUART_Buffer++;
        /* Test if the end of string has been reached */
        if (*pUART_Buffer==0)
        {
            /* String has been sent */
            pUART_Buffer = 0;
            /* Indicate that the UART is now ready to send */
            UART_Ready   = 1;
            return;
        }
        /* Send next character in string */
        UDR = *pUART_Buffer;
        return;
    }
    /* Indicate that the UART is now ready to send */
    UART_Ready = 1;
}

/* UART Receive Complete Interrupt Function */
SIGNAL(SIG_UART_RECV)      
{


  /* Indicate that the UART has received a character */
    UART_ReceivedChar = 1;
    /* Store received character */
    UART_RxChar = UDR;
	/*
if (UART_RxChar == NORMAL_COMMAND) {
		robot.vitesse = UART_RxChar;
		robot.angle = UART_RxChar;
}
*/
    /*switch (state){
      case 0:  
        if (UART_RxChar == NORMAL_COMMAND){
          state = 1;
        }
        else if(UART_RxChar == FORCED_STOP)
        {
          state = 1;
        }
      break;
      
      case 1:
        robot.vitesse = UART_RxChar;
        state = 2;
      break;
      
      case 2:
        robot.angle = UART_RxChar;
      break;
     
      default:
        state = 0;
      break;
	  
    }*/
	UDR = UART_RxChar;
}

void UART_SendByte(uint8_t Data)
{   
    /* wait for UART to become available */
    while(!UART_Ready);
    UART_Ready = 0;
    /* Send character */
     Data=UDR ;
}

uint8_t UART_ReceiveByte(void)
{
    /* wait for UART to indicate that a character has been received */
    while(!UART_ReceivedChar);
    UART_ReceivedChar = 0;
    /* read byte from UART data buffer */
    return UART_RxChar;
}


void initUART(void)
{
    UART_Ready        = 1;
    UART_ReceivedChar = 0;
    pUART_Buffer      = 0;
    /* configure asynchronous operation, no parity, 1 stop bit, 8 data bits, Tx on rising edge */
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
    /* enable RxD/TxD and ints */
    UCSRB = (1<<RXCIE)|(1<<TXCIE)|(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);       
    /* set baud rate */
    UBRRH = (uint8_t)(UART_BAUD_SELECT >> 8);          
    UBRRL = (uint8_t)(UART_BAUD_SELECT & 0x00FF);          
    /* enable interrupts */
    sei();
}

