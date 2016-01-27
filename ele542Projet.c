

#include "uart.h"
#include <avr/pgmspace.h>

#include <stdlib.h> 
 

/* COMMAND	*/
const u08 NORMAL_COMMAND = 0xF1;
const u08 FORCED_STOP	=	0xF0;


int main(void)
{
    u08 data;
	u08 p_vitesse=0,vitesse=0;


	u08 p_angle=0,angle=0;
	short etat;
	etat = 0;
	
	char str[30];;
    /* Initialise UART */
    UART_Init();
	
	for (;;) { 
	printf("hhhhhhhhhhhhhhhhhhhhhhhhhhh"); /* loop forever */
	//sleep(1000);
		data = UART_ReceiveByte();
				//	send_debugu08(data);
				//	for(int i=0;i<40000;++i){}
				//	sprintf(str, "%d", data );
					
				/*	send_debug(str,30);
					for( int j=29;j>=0;j--)
					{
						send_debugu08(str[j]);
					}*/
		switch(etat)
		{
			case 0:
				if (data == NORMAL_COMMAND)
				{
					//send_debug("debug: etat = 0: data: ", 17);
					//send_debugu08(data);
					etat = 1;
				}
				break;
			case 1:

				vitesse = data;
				if (vitesse != p_vitesse) {
					UART_SendByte(vitesse);
					
				
					send_debug(" debug: etat = 1; vitesse= ", 28);
					
					int vit;
					scanf(vitesse, "%vit", &vit);
					send_debugu08(vit);
					//send_debug_int(atoi(vitesse));
					
					p_vitesse = vitesse;
				}
				etat = 2;
				break;
			case 2:

				if(angle != p_angle)
				{
					angle = data;
					UART_SendByte(angle);
					send_debug(" debug: etat = 2; angle= ", 25);
					send_debugu08(angle);
					p_angle = angle;
				}
				etat = 0;
				break;

		}
	
    }
}
