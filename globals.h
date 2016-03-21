/*
 *	DEFINE for bit operations	
 */
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "stdlib.h"
 #include  "stdio.h"
 #include  <avr/io.h>
 #include  <avr/iom32.h>
 #include  <avr/wdt.h>


#define BIT(n)	            ( 1<<(n) )
//  BIT MACROS
#define BIT_SET(y,mask)     ( y |=  (mask) ) 
#define BIT_CLEAR(y,mask)   ( y &= ~(mask) ) 
#define BIT_FLIP(y,mask)    ( y ^=  (mask) )
#define BIT_CHECK(y,mask)   ( y & (1<<mask) )

//  BYTE MACROS
#define BYTE_SET(y,val)     (y = val)
#define BYTE_CLEAR(y)       (y=0x00)
#define BYTE_FLIP(y)        (~y)
#define BYTE_CHECK(y)       (y)


#define DEG_TO_RAD(angle)       ( (float)angle * 0.03490658504 ) //(2*PI)/180
#define SPEED_CONVERSION(speed) ( ((float)speed * 100) - 1.0 )
/*
 *	
 */
#define F_CPU 16000000UL
#define F_PWM 200
#define PRESCALER 64
#define PWM_TOP ((F_CPU/(PRESCALER*F_PWM)) -1)


#define FALSE 0
#define TRUE 1



/* 
 * structures pour definir la liste des ports et des pins utilisees
 *
 */
typedef enum {false, true} boolean;

/* ADC */
typedef struct {
  uint8_t VG:1;
  uint8_t VD:1;
  uint8_t DIR_G:1;
  uint8_t DIR_D:1;
  uint8_t CAL:1;
  uint8_t UNUSED:1;
  uint8_t SW6:1;
  uint8_t SW7:1;

}_PORTA;

/* LED */
typedef struct {
  uint8_t UNUSED:1;
  uint8_t LED1:1;
  uint8_t LED2:1;
  uint8_t LED3:1;
  uint8_t LED4:1;
  uint8_t LED5:1;
  uint8_t LED6:1;
  uint8_t LED7:1;

}_PORTB;


/* TWI */
typedef struct {
  uint8_t SCL:1;
  uint8_t SDA:1;
  uint8_t UNUSED:6;

}_PORTC;
/*
 * *  for timer#1
 *   PWM_G and PWM_D
 */
typedef struct {
  uint8_t UNUSED:2;
  uint8_t DIR_G1:1;
  uint8_t DIR_G2:1;
  uint8_t PWM_G:1;
  uint8_t PWM_D:1;
  uint8_t DIR_D1:1;
  uint8_t DIR_D2:1;

}_PORTD;

typedef struct {
 _PORTA portA;
 _PORTB portB;
 _PORTC portC;
 _PORTD portD;

}Ports;


/*
 * Directions du moteur
 */ 
typedef enum {
  NEUTRE, /* 00 */
  AVANT,  /* 01 */
  ARRIERE,/* 10 */
  FREIN   /* 11 */

}direction;

/* motors directions */
typedef struct {
  direction left;
  direction right;
}Directions;

/* data from UART */
typedef struct {
  volatile float vitesse;
  volatile float angle;

}Data;


/* Duty cycles for lef and right motors */
typedef struct {
  volatile float left;
  volatile float right;

}DutyCycles;

/* ADC for right and left motors */
typedef struct {
  volatile float left;
  volatile float right;
} _ADC

/* main structure */
typedef struct {
  _ADC  adc;
  Ports ports;
  DutyCycle dutyCycles; 
  Data data;
  Directions directions;
  volatile boolean calibrated;
}Robot;


#endif
