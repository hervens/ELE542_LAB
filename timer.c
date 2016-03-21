#include "timer.h"



//genere signal pwm au moteur a l'aide du timer 1
void updateMoteur( float Duty_G, float Duty_D)
{
      if (robot.data.vitesse != 0){
	if(robot..directions.left){
                

        }
      }	


	if((Duty_G < 0) && (Duty_D < 0))
	{
		
	//	iDutyG = iDutyG * -1;
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G2)); //SET BIT 3
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G1)); //CLEAR BIT 2

		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D2)); //7
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D1)); //6
	}
	else if ((Duty_G > 0) && (Duty_D > 0))
	{
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G1)); 
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G2)); 
		
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D1)); 
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D2)); 

	}
	else if((Duty_G > 0) && (Duty_D < 0))
	{
	
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G1)); //SET BIT 3
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G2)); //CLEAR BIT 2
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D2)); //SET BIT 3
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D1)); //CLEAR BIT 2 
	}
	else if((Duty_G < 0) && (Duty_D > 0))
	{

	
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G2)); //SET BIT 3
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G1)); //CLEAR BIT 2
		BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D1)); 
		BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D2)); 
	}
	else
	{
		PORTD |=  (1<<3); //3
		PORTD |= (1<<2);// 2

		PORTD |= (1<<6); //6
		PORTD |= (1<<7);// 7
	}
	
/*	OCR1A = iDutyG;
	OCR1B = iDutyD;
*/	

}


void setDirection (direction directionG, direction directionD)
{
	
	switch(directionG)
	{
		case NEUTRE:
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G1));
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G2));
		break;
		case AVANT:
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G1));
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G2));
		break;
		case ARRIERE:
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_G1));
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G2));
		break;
		case FREIN:
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G1));
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_G2));
		break;

              
	}
	switch(directionD)
	{
		case NEUTRE:
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D1));
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D2));
		break;
		case AVANT:
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D1));
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D2));
		break;
		case ARRIERE:
			BIT_CLEAR	(PORTD,BIT(robot.ports.portD.DIR_D1));
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D2));
		break;
		case FREIN:
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D1));
			BIT_SET		(PORTD,BIT(robot.ports.portD.DIR_D2));
		break;
	}
}


void setPWM(uint8_t gauche, uint8_t droite) {

	volatile uint16_t temp=((gauche * PWM_TOP) / 100); // voir PWM_TOP/100 = 12.49
	OCR1A = temp;

	temp=((droite * PWM_TOP) /100);
	OCR1B = temp;
}

//doc pg 105

/************************************************************************** 
 * interrupt vector see (https://cours.etsmtl.ca/ele542/labo/Ref-STK500-ATMega32/ATMega32-Complete.pdf)
 * p.42
 *
 *
 * * TCCR1A   : Timer/Counter1 Control Register A
 *            -COM1A1   : Compare Output Mode for Compare unit A  (bit 7)
 *            -COM1B1   : Compare Output Mode for Compare unit B  (bit 5)
 *            -WGM11    : Waveform Generation Mode                (bit 1) 
 *              -mode 14 (watch below WGM13/12)
 *              -update of OCR1x TOP / TOV1 Flag Ste on TOP
 *              -TOP ICR1
 *
 * * TCCR1B   : Timer/Counter1 Control Register B
 *            -WGM13/12   : Waveform Generation Mode    (bits 4:3)
 *            -CS11       : Clock Select(prescaler 8)   (bit 1)
 *
 * * TIMSK    : Timer/Counter1 Interrupt Mask
 *            -TICIE1 : Timer/Counter1 Input Capture Interrupt Enable           (bit 5)
 *            -OCIE1A : Timer/Counter1, Output Compare A Match Interrupt Enable (bit 4)
 *            -OCIE1B : Timer/Counter1, Output Compare B Match Interrupt Enable (bit 3)
 *            -TOIE1  : Timer/Counter1, Overflow Interrupt Enable               (bit 2)
 *
 * * TIFR     : Timer/Counter Interrupt Flag Register
 *            -ICF1   : Timer/Counter1, Input Capture Flag (for WMGM13:0)=counter reaches TOP value
 *            -OCF1A  : OCIE1A is executed when the OCF1A Flag, located in TIFR, is set   (bit 5)
 *            -OCF1B  : OCIE1B is executed when the OCF1B Flag, located in TIFR, is set   (bit 4)
 *            -TOV1   : TOEE1 is executed when the TOV1 Flag, located in TIFR, is set.    (bit 2)
 *            -ICR1   : TOP value of the PWM       
 *
 ***************************************************************************/
void initTimer()
{
//	DDRD = 0xFE;
	//PIND = 0xFF;
	TCCR1A =  (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B = ((1<<WGM12) |(1<<WGM13) | (1<<CS11));
	TIMSK  = ((1<<TOIE1) | (0<<OCIE1B)| (0<<OCIE1A) | (0<<TICIE1));
	TIFR   = ((1<<ICF1)| (1<<OCF1A)| (1<<OCF1B)| (1<<TOV1));
	ICR1   = PWM_TOP; //10000

	setPWM(0,0);	
}

ISR(TIMER1_OVF_vect) {

  if(robot.calibrated == TRUE) {
	setDirection(robot.directions.left,robot.directions.right);
	setPWM(robot.dutyCycles.left,robot.dutyCycles.right);
  }
  else
  {
    setPWM(0,0);
  }  
	


}
