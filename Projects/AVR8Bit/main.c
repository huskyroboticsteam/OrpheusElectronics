#include "conf.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <string.h>
#include "pwm.h"
#include "encoder.h"
#include "motor.h"
#include "timers.h"
#include "adc.h"
#include "can.h"
#include "usart.h"
/*struct CAN_msg {
	uint16_t id;
	uint8_t flags;
	uint8_t length;
	uint8_t data[8];
};*/


int main(){
	int i;
	DDRE = (1 << PE4) | (1 << PE3);
	setup_timers();
	usart_init(19200);
	_delay_ms(666);
	sei();
	init_encoder();
	PORTE = 0;
	volatile int itg = 0;
	volatile int error;
	int target = 256;
	int lft = 0;
	int dt=0;
	int last;
	int last_d;
	int vel;
	int pwm;
	int cnt = 0;
	while(1){
		//vel = vel/2 + get_encoder_velocity()/2;
		vel = get_encoder_ticks();
		error = target - vel;
		dt = error - last;
		last = error;
		//int pwm = error/4 + itg/16 + dt/8;
		if(error > 1024) error = 1024;
		if(error < -1024) error = -1024;
		pwm = error*11 + itg/3 + dt*6;
		
		if(error > 4 || error < -4){
			itg += error;
		}
		if(itg > 2048) itg = 2048;
		if(itg < -2048) itg = -2048;
		if(pwm > 1023) pwm = 1023;
		if(pwm < -1023) pwm = -1023;
		tprintf("%d %d %d %d %d %d\n", target, vel, error, itg/10, dt*10, pwm);
		//tprintf("%d\n", itg);
		set_motor_power(pwm);
		delay_mS(20);
		//cnt++;
		//if(cnt % 256 == 0){
		if(!(PINE & (1<<PE5))){
			target+=64;
		} else {
			//target-=64;
			target -= 32;
			if(target < 256){
				target = 256;
			}
		}
		//}
		//tprintf("%l\n", get_encoder_velocity());
		//delay_mS(100);
		/*if(error < 5){
			lft++;
			if(lft > 20){
				if(target == 0){
					target = 8192;
				} else {
					target = 0;
				}
				lft = 0;
			}
		} else {
			lft = 0;
		}*/
	}
}