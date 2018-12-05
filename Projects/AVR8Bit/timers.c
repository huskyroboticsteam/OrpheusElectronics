#include "conf.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timers.h"

volatile uint32_t TOF_Cnt; //Timer1 overflow counter

/*Will this eat too much CPU time? TBD*/
ISR(TIMER1_OVF_vect){ //This should fire every 10mS
	TOF_Cnt++;
}

/*Set up the AVR's timers for PWM and time information*/
void setup_timers(){
	//Timer 0: Phase correct PWM, CLK/64
	TCCR0A = (1<<CS01) | (1<<CS00) | (1<<WGM00);
	TIMSK0 = (1 << TOIE0); // For velocity calculation. Fires every 2.05mS
	
	//Timer 1: Fast PWM, TOP=OCR1A, CLK/64
	//This makes timer 1 increment every 8 microseconds at 8 Mhz or every 4uS at 16MHz
	TCCR1B = (1<<CS11) | (1<<CS10)  | (1<<WGM13) | (1<<WGM12);
	TCCR1A = (1<<WGM11) | (1<<WGM10);
	OCR1A = 10000; //Count to 10000 before resetting
	TCNT1 = 0;
	TIMSK1 = (1 << TOIE1); //Enable interrupt on match
	
	//Timer 3: 10-bit phase correct PWM, CLK/64
	TCCR3A = (1<<WGM31) | (1<<WGM30);
	TCCR3B = /*(1<<CS30) | */(1<<CS31);

	TOF_Cnt = 0; //Clear the overflow counter
}

/*Returns the number of milliseconds since timer initalization*/
uint32_t get_mS(){
	uint16_t timer_ticks = TCNT1;
	#if F_CPU == 8000000
	return (TOF_Cnt * 80) + (timer_ticks/125L); //8 Mhz
	#else
	return (TOF_Cnt * 40) + (timer_ticks/250L); // 16 Mhz
	#endif
}

/*Returns the number of microseconds since system initalization*/
uint32_t get_uS(){
	uint16_t timer_ticks = TCNT1;
	#if F_CPU == 8000000
	return (TOF_Cnt * 80000) + (timer_ticks << 3); //8 MHz
	#else
	return (TOF_Cnt * 40000) + (timer_ticks << 2); //16 MHz
	#endif
}

/*delay for the specified number of milliseconds*/
void delay_mS(uint16_t mS){
	uint32_t start = get_mS();
	while(get_mS() - start < mS);
}