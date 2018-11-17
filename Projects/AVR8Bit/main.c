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
void dump_message(struct CAN_msg m){
	tprintf("\n-CAN MESSAGE-\n");
	tprintf("id=%d, flags=0x%X, length=%d\n", m.id, (long)m.flags, m.length);
	tprintf("HEX={");
	for(int i = 0;i < m.length;i++){
		tprintf("%X%s", (long)m.data[i], i == m.length-1?"": " ");
	}
	tprintf("}, ASCII={");
	for(int i = 0;i < m.length;i++){
		tprintf("%c", (m.data[i] > 31 && m.data[i] < 128)?m.data[i]: '.');
	}
	tprintf("}\n-END CAN MESSAGE-\n\n");
}
int main(){
	int i;
	setup_timers();
	usart_init(1200);
	init_CAN(0, 3, 0);
	DDRE = 1<<PE4;
	sei();
	delay_mS(2000);
	struct CAN_msg m, r;
	m.id = 1;
	m.flags = 0;
	m.length = 2;
	m.data[0] = 'H';
	m.data[1] = 'i';
	while(1){
		tprintf("Sending msg...\n");
		int res = CAN_send_msg(&m);
		if(!res){
			tprintf("Queing message failed!\n");
		}
		//CAN_dump_state(); 
		while(res=CAN_msg_available()){
		tprintf("%d RX messages available\n", res);
			CAN_get_msg(&r);
			dump_message(r);
		}
		delay_mS(250);
		PORTE ^= 1<<PE4;
	}
}