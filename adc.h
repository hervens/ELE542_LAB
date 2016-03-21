#ifndef __ADC_H_
#define __ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
extern Robot robot;
float getAvgSpeedMoteurDroit();
float getAvgSpeedMoteurGauche();
void initAdc();
void calibration();

typedef struct {

uint16_t vMaxPosG;
uint16_t vMaxNegG;
uint16_t vZeroPosG;
uint16_t vZeroNegG;

uint16_t vMaxPosD;
uint16_t vMaxNegD;
uint16_t vZeroPosD;
uint16_t vZeroNegD;
}calibrate;



#endif
