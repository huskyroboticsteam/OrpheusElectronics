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

int main(){
	int i;
	setup_timers();
	usart_init(1200);
	init_CAN(0, 3, 0);
	DDRE = 1<<PE4;
	sei();
	struct CAN_msg m;
	m.id = 1;
	m.flags = 0;
	m.length = 2;
	m.data[0] = 'H';
	m.data[1] = 'i';
	while(1){
		tprintf("Sending CAN message...");
		CAN_send_msg(&m);
		tprintf("av=%d\n", CAN_msg_available());
		CAN_dump_state(); 
		delay_mS(250);
		PORTE ^= 1<<PE4;
	}
}