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
	int speed = 0;
	struct CAN_msg m;
	char s[5];
	setup_timers();
	set_LED(0, 2);
	usart_init(19200); //Debug serial
	_delay_ms(666); //Delay so one can connect to debug serial
	sei();
	uint16_t my_address = 0x10;
	//CAN_set_RX_filter(my_address, my_address);
	init_CAN(CAN_100_BAUD, 4, 0);
	send_int8_packet(0, 0);
	delay_mS(500);
	while(1){
		if(CAN_msg_available()){
			CAN_get_msg(&m);
			dump_CAN_message(m);
		}
		if(usart_available()){
			read_string(s, '\r');
			uint16_t speed = atoi(s);
		}
		send_int8_packet(int_abs(speed), speed < 0);
	}
}