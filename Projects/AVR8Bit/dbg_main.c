#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <string.h>
#include <stdlib.h>
#include "pwm.h"
#include "encoder.h"
#include "motor.h"
#include "timers.h"
#include "adc.h"
#include "can.h"
#include "usart.h"
#include "servo.h"
#include <util.h>
/*struct CAN_msg {
	uint16_t id;
	uint8_t flags;
	uint8_t length;
	uint8_t data[8];
};*/

void read_string(char*,char);

int main(){
	//DDRE = (1 << PE4) | (1 << PE3);
	PORTA = 0xF0;
	setup_timers();
	usart_init(19200);
	//_delay_ms(666);
	sei();
	//cli();
	tprintf("Hello, World!\n");
	//tprintf("MCUSR=%X\n", (uint32_t)MCUSR);
	//MCUSR = 0;
	init_encoder();
	init_ADC();
	DDRA = 0xF0;
	//PORTA = 0xFF;
	//extern uint8_t LED_states;
	//LED_states = 0xFF;
	/*set_LED(0, 3);
	set_LED(1, 3);
	set_LED(2, 3);
	set_LED(3, 3);*/
	//PORTA = 0xF0;
	init_motor();
	init_servo();
	//init_ADC();
	//delay_mS(1000);
	_delay_ms(1000);
	//set_motor_mode(MOTOR_MODE_PID);
	enable_motor();
	PORTE = 1<<PE4;
	//PORTE = 0;
	//char target_string[8], vel_string[8];
//	set_Kp(0, 10);
//	set_Ki(0, 3);
//	set_Kd(0, 2);
	//i = 0;
	int i = 0;
	int d = 2;
	//set_motor_power(1023);
	set_LED(0, 0);
	set_LED(1, 0);
	set_LED(2, 3);
	set_LED(3, 0);
	while(1){
	/*	if(!PID_due && usart_available()){
			read_string(target_string, ' ');
			read_string(vel_string, '\r');
			//tprintf("\nGot \"%s\", \"%s\"\n", target_string, vel_string);
			uint16_t a = atoi(target_string);
			uint16_t b = atoi(vel_string);
			tprintf("%l, %l\n", (uint32_t)a, (uint32_t)b);
			set_target_velocity(a);
			set_target_position(b);
		}*/
		//motor_control_tick();
		//tprintf("Tick\n");
		uint32_t c = 0;
		for(int i = 0;i < 256;i++){
			c += get_motor_current();
		}
		c /= 256;
		//tprintf("%dmV %dmA\n", (uint16_t)get_voltage(), c);
		
		tprintf("pwm=%d, %l ticks, %dmV %dmA\n", (uint16_t)i, (uint32_t)get_encoder_ticks(), (uint16_t)get_voltage(), (uint16_t)get_motor_current());
		int ls = get_motor_limit_switch_state();
		/*if(ls){
			if(ls & 1){
				tprintf("LS1 ");
			}
			if(ls & 2){
				tprintf("LS2");
			}
			tprintf("\n");
		}*/
		set_motor_power(i);
		i += d;
		if(i < -0){
			d = 2;
		}
		if(i > 200){
			d = -2;
		}
		if(i > 0 && i < 180){
			set_servo_position(i);
		}
	//tprintf("%d\n", get_motor_limit_switch_state());
	//	delay_mS(1000);
		//set_motor_power(0);
		//delay_mS(300);
		_delay_ms(100);
	}
}