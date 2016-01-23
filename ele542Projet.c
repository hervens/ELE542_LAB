#include "uart.h"
#include <avr/pgmspace.h>


/*	DEBUG	*/
#define START_DEBUG 0xFE
#define END_DEBUG 0xFF

/* COMMAND	*/
#define NORMAL_COMMAND 	0xF1
#define FORCED_STOP		0xF0

#define PI 3.1415



void deg_to_rad(int deg){

	float res;

}


int main(void)
{
    u08 data;
	u08 speed;
	u08 angle;
    /* Initialise UART */
    UART_Init();
	
	data = 'c';
	UART_SendByte(START_DEBUG);
	UART_SendByte(data);
	UART_SendByte(END_DEBUG);

	speed = 120;
	angle = 90;

	UART_SendByte(NORMAL_COMMAND);
	UART_SendByte(0x56);
	UART_SendByte(0x56);

    PRINT("Hello World !");
    EOL();

    for (;;) {  /* loop forever */
        UART_SendByte(START_DEBUG);
			data=UART_ReceiveByte();
			UART_Printfu16(data);
				UART_SendByte(END_DEBUG);
		/*	if(data==FORCED_STOP){
		UART_SendByte(START_DEBUG);
				UART_SendByte(START_DEBUG);
				UART_Printfu08(data);
			/*	UART_SendByte(data);
				UART_SendByte(END_DEBUG);
			}
*/
		/*PRINT("Press any key...");
        EOL();
    
        data = UART_ReceiveByte();
    
        PRINT("You pressed '");
        UART_SendByte(data);
        PRINT("' which is 0x");
        UART_Printfu08(data);
        PRINT(" in hexadecimal.");
        EOL();*/
    }
}
