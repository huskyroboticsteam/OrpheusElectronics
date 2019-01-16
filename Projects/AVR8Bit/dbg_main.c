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
/*struct CAN_msg {
	uint16_t id;
	uint8_t flags;
	uint8_t length;
	uint8_t data[8];
};*/

void read_string(char*,char);

int main(){
	int i;
	DDRE = (1 << PE4) | (1 << PE3);
	setup_timers();
	usart_init(19200);
	_delay_ms(666);
	sei();
	tprintf("Hello, World!\n");
	delay_mS(1000);
	init_encoder();
	init_motor();
	set_motor_mode(MOTOR_MODE_PID);
	enable_motor();
	PORTE = 0;
	char target_string[8], vel_string[8];
	while(1){
		if(!PID_due && usart_available()){
			read_string(target_string, ' ');
			read_string(vel_string, '\r');
			//tprintf("\nGot \"%s\", \"%s\"\n", target_string, vel_string);
			int a = atoi(target_string);
			int b = atoi(vel_string);
			set_target_velocity(a);
			set_target_position(b);
		}
		motor_control_tick();
	}
}