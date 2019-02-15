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
#include "messaging.h"
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
	usart_init(19200); //Debug serial
	_delay_ms(666); //Delay so one can connect to debug serial
	sei();
	//set_LED(2, 3);
	uint16_t my_address = 0x10;
    CAN_set_RX_filter(0x1F, 0x10);
	tprintf("CAN init\n");
	DDRA = 0xF0;
	init_ADC();
	init_motor();
	enable_motor();
	//PORTA = 0xFF;
	//PORTA = PORTA << 4;
	init_CAN(CAN_125_BAUD, 4, 0);
	//CAN_set_RX_filter(1<<11, my_address);
	delay_mS(1000);
	//set_LED(2, 0);
	while(1){
		if(CAN_msg_available()){
			//CAN_dump_state();
			CAN_get_msg(&m);
			dump_CAN_message(m);
			handle_CAN_message(&m);
			set_LED(1, 3);
		}
		//tprintf("%d ", (uint16_t)get_voltage());
		//CAN_dump_state();
		delay_mS(250);
		set_LED(1, 0);
	}
}