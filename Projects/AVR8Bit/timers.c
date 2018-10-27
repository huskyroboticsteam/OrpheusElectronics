#include "conf.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timers.h"

volatile uint32_t TOF_Cnt; //Timer1 overflow counter

/*Will this eat too much CPU time? TBD*/
ISR(TIMER1_COMPA_vect){ //This should fire every 10mS
	TOF_Cnt++;
}

/*Set up the AVR's timers for PWM and time information*/
void setup_timers(){
	//Timer 0: Phase correct PWM, CLK/64
	TCCR0A = (1<<CS01) | (1<<CS00) | (1<<WGM00);
	
	//Timer 1: Fast PWM, TOP=OCR1A, CLK/8
	//This makes timer 1 increment every microsecond at 8 Mhz or every 500nS at 16MHz
	TCCR1B = (1<<CS11) | (1<<WGM13) | (1<<WGM12) | (1<<WGM11) | (1<<WGM10);
	OCR1A = 10000; //Count to 10000 before resetting
	TCNT1 = 0;
	TIMSK1 = (1 << OCIE1A); //Enable interrupt on match
	
	//Timer 3: 10-bit phase correct PWM, CLK/8
	TCCR3B = (1<<CS21) | (1<<WGM21) | (1<<WGM20);
	
	TOF_Cnt = 0; //Clear the overflow counter
}

/*Returns the number of milliseconds since timer initalization*/
uint32_t get_mS(){
	uint16_t timer_ticks = TCNT1;
	#if F_CPU == 8000000
	return (TOF_Cnt * 10) + (timer_ticks/1000); //8 Mhz
	#else
	return (TOF_Cnt * 5) + (timer_ticks/2000); // 16 Mhz
	#endif
}

/*Returns the number of microseconds since system initalization*/
uint32_t get_uS(){
	uint16_t timer_ticks = TCNT1;
	#if F_CPU == 8000000
	return (TOF_Cnt * 10000) + timer_ticks; //8 MHz
	#else
	return (TOF_Cnt * 5000) + (timer_ticks >> 1); //16 MHz
	#endif
}

/*delay for the specified number of milliseconds*/
void delay_mS(uint16_t mS){
	uint32_t start = get_mS();
	while(get_mS() - start < mS);
}