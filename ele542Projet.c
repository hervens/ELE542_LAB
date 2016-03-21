#include <avr/pgmspace.h>
#include <stdlib.h> 

#include "globals.h"
#include "uart2.h"
#include "adc.h"
#include "timer.h"
#include "moteur.h"


ROBOT robot;



/* COMMAND	*/

float  Vitesse_D,  Angle_D,  Vg,  Vd;
float Duty_G = 0.0, Duty_D = 0.0;
uint8_t p_vitesse=0; //valeure la plus récente de la vitesse
uint8_t p_angle=0; //valeure la plus récente de l'angle
uint8_t vitesse;
uint8_t angle;


float getUartVitesse();
float getUartAngle();
void bougeMoteur();
void lireTelecommande();

int main(void)
 {
        //Init Motor
     /*
        BYTE_SET(DDRD,0xFE);
        PORTB = 0xFF;
        PORTB = 0xC0;
        DDRA  = 0x10;
        PORTA = 0x00;
       */ 
		
		initAdc();
		initUART();
		initTimer();
	//	DDRC=0xFF;
		

		//Enable interrupt after all init else Infinite loop
        sei();
        
       	calibration(); 

        //Enable_watchdog(WDTO_500MS);

	for (;;) 
	{  /* loop forever */
//		lireTelecommande();
/*		if(timerOvf == 1)
		{

		*/
	Vitesse_D = getUartVitesse();
	Angle_D = getUartAngle();
	Vg = getAvgSpeedMoteurGauche();
	Vd = getAvgSpeedMoteurDroit();

	CalculPWM(Vitesse_D,Angle_D,Vg,Vd,&Duty_G,&Duty_D);

		/*	timerOvf = 0;
		}
  */  
	}
}


/*
	La vitesse et l'angle la plus récente est égale a p_vitesse et p_angle
*/
/*
void lireTelecommande()
{
	uint8_t data;
	data = UART_ReceiveByte();
	vitesse = 0;
	angle = 0;
	if (data == NORMAL_COMMAND) {
		robot.vitesse = UART_ReceiveByte();
		robot.angle = UART_ReceiveByte();
	}
}
*/
void bougeMoteur()
{

	
    updateMoteur(Duty_G, Duty_D);
	setPWM(Duty_G,Duty_D);
}

//transforme la vitesse en format -1 < v < 1
float getUartVitesse()
{       
	return SPEED_CONVERSION(robot.vitesse);
}

//transforme l.angle en format 0 a 2PI
float getUartAngle()
{
	return DEG_TO_RAD(robot.angle);
}
