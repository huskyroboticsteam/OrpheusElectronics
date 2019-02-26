#include <avr/io.h>
#include <avr/interrupt.h>
#include <timers.h>
#include <servo.h>

ISR(TIMER1_COMPB_vect){
	PORTC &= ~(1<<4);
}

void inline servo_high(){
	PORTC |= 1<<4;
}

void init_servo(){
	 TIMSK1 |= (1 << OCIE1B);
	 DDRC |= 1<<4;
	 OCR1B = 375;
}

void set_servo_position(int degrees){
	if(degrees > 180) return;
	if(degrees < 2) degrees = 2;
	OCR1B = degrees * 2 + degrees / 2;
}