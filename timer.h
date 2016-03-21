#ifndef __TIMER_H_
#define __TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h" 
extern Robot robot;

volatile char timerOvf;

void initTimer();
void updateMoteur(float Duty_G, float Duty_D);
void setPWM(uint8_t gauche, uint8_t droite);

void setDirection (direction directionG, direction directionD);

#endif
