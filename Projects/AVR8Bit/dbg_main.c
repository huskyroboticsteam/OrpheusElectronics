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
#include <util.h>
/*struct CAN_msg {
	uint16_t id;
	uint8_t flags;
	uint8_t length;
	uint8_t data[8];
};*/

void read_string(char*,char);

int main(){
	int i;
	//DDRE = (1 << PE4) | (1 << PE3);
	setup_timers();
	usart_init(19200);
	_delay_ms(666);
	sei();
	tprintf("Hello, World!");
	init_encoder();
	init_ADC();
	DDRA = 0xF0;
	//PORTA = 0xFF;
	//extern uint8_t LED_states;
	//LED_states = 0xFF;
	set_LED(0, 0);
	set_LED(1, 1);
	set_LED(2, 2);
	set_LED(3, 3);
	init_motor();
	init_ADC();
	
	//set_motor_mode(MOTOR_MODE_PID);
	//enable_motor();
	//PORTE = 0;
	char target_string[8], vel_string[8];
	set_Kp(0, 10);
	set_Ki(0, 3);
	set_Kd(0, 2);
	i = 0;
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
		delay_mS(100);
	}
}