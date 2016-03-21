#include "adc.h"
#include "timer.h"

/* Global variable */
volatile unsigned char currentChannel = 0;
volatile unsigned int moteurGauche, moteurDroite;
volatile short sumMoteurGauche = 0, sumMoteurDroit= 0;
volatile short countMoteurGauche=0, countMoteurDroit = 0;
volatile float speedMoteurGauche = 0;
volatile float speedMoteurDroit = 0;

calibrate cal;
//calibration



/* Interrupt service rutines */

ISR (ADC_vect){
	
	ADMUX = currentChannel;//Update the ADMUX register
	if(currentChannel == 0x00)//channel 0
	{
		moteurGauche = ADC;
	 	currentChannel = 1;

		if(countMoteurGauche < 5)
		{
			sumMoteurGauche += moteurGauche;
			countMoteurGauche++;
		}
		else
		{
			speedMoteurGauche =	sumMoteurGauche / countMoteurGauche;
			countMoteurGauche = 0;
			sumMoteurGauche = 0;
		}
	 }
	else
	{
		moteurDroite = ADC;
		currentChannel = 0;

		if(countMoteurDroit < 5)
		{
			sumMoteurDroit += moteurDroite;
			countMoteurDroit++;
		}
		else
		{
			speedMoteurDroit = sumMoteurDroit / countMoteurDroit;
			countMoteurDroit = 0;
			sumMoteurDroit = 0;
		}
	}

}




//retourne la valeur moyenne produte par l'ADC des
// 10 dernieres valeures
float getAvgSpeedMoteurDroit()
{
	//comment acceder bits A2 et A3 pour savoir si valeure positive ou negative?

	if(PORTA & (1<<3)) //negatif
	{
		return - ( ( (float)speedMoteurDroit - (float)cal.vZeroNegD )  / ( (float)cal.vMaxNegD - (float)cal.vZeroNegD ) );
	}
	else
	{
		return - ( ( (float)speedMoteurDroit - (float)cal.vZeroPosD )  / ( (float)cal.vMaxPosD - (float)cal.vZeroPosD ) );
	}
}

float getAvgSpeedMoteurGauche()
{
	if(PORTA & (1<<2)) //negatif
	{
		return - ( ( (float)speedMoteurDroit - (float)cal.vZeroNegG )  / ( (float)cal.vMaxNegG - (float)cal.vZeroNegG ) );
	}
	else
	{
		return - ( ( (float)speedMoteurDroit - (float)cal.vZeroPosG )  / ( (float)cal.vMaxPosG - (float)cal.vZeroPosG ) );
	}
}
/************************************************************************** 
 * * ACSR   : Analog Comparator Control and Status Register
 *            -ACD  : Analog Comparator Disable (bit 7)
 *
 * * ADCSRA : ADC Control and status Register A
 *            -ADEN : ADC Enable                (bit 7)
 *            -ADSC : ADC Start Conversion      (bit 6)
 *            -ADATE: ADC Auto Trigger Enable   (bit 5)
 *            -ADIE : ADC Interrupt Enable      (bit 5)
 *            -ADSP : ADC Prescaler Select Bits (bits 2:0) 128
 *
 * * ADMUX  : ADC Multiplexer Selection Register
 *            -ADMUX: Analog Channel and Gain Selection Bits (bits 4:0)
 *
 ***************************************************************************/

void initAdc()
{	// Ajout
	//ACSR= (1<< ACD);
	// init
	ADCSRA = ((1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE));
	ADMUX = 0x00;
	// Ajout
   	SFIOR= (0<<ADTS0) | (0 << ADTS1) | (0 << ADTS2) ;
	
}

void wait()
{
	int i;
	for(i = 0; i < 10; i++)
	{
		timerOvf = 0;
		while(timerOvf != 1) {}
		timerOvf = 0;
		while(timerOvf != 1) {}
	}
}

void calibration()
{
        robot.calibrated = FALSE;


        BIT_SET(DDRA,BIT(robot.portA.CAL));

        BIT_SET(PORTA,BIT(robot.portA.CAL));
	//vMax+
        setDirection(ARRIERE,AVANT);
	
//	wait();
	cal.vMaxPosD = speedMoteurDroit;
	cal.vMaxPosG = speedMoteurGauche;

	//vZero+
        BIT_CLEAR(PORTA,BIT(robot.portA.CAL));

	
//	wait();
	cal.vZeroPosD = speedMoteurDroit;
	cal.vZeroPosG= speedMoteurGauche;


        BIT_SET(PORTA,BIT(robot.portA.CAL));
	//vMax-
        setDirection(AVANT,ARRIERE);
	
  //      wait();
	cal.vMaxNegD = speedMoteurDroit;
	cal.vMaxNegG = speedMoteurGauche;

        BIT_CLEAR(PORTA,BIT(robot.portA.CAL));
	//vZero-
//	wait();
	cal.vZeroNegD = speedMoteurDroit;
	cal.vZeroNegG = speedMoteurGauche;
        robot.calibrated = TRUE;

}

