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
	int i;
	tprintf("\n-CAN MESSAGE-\n");
	tprintf("id=%d, flags=0x%X, length=%d\n", m.id, (long)m.flags, m.length);
	tprintf("HEX={");
	for(i = 0;i < m.length;i++){
		tprintf("%X%s", (long)m.data[i], i == m.length-1?"": " ");
	}
	tprintf("}, ASCII={");
	for(i = 0;i < m.length;i++){
		tprintf("%c", (m.data[i] > 31 && m.data[i] < 128)?m.data[i]: '.');
	}
	tprintf("}\n-END CAN MESSAGE-\n\n");
}
int main(){
	int i;
	DDRE = (1 << PE4);
	setup_timers();
	usart_init(1200);
	init_encoder();
	_delay_ms(666);
	init_CAN(CAN_100_BAUD, 3, 0);
	DDRE = 1<<PE4;
	PORTE = (1<<PE6) | (1<<PE7);
	sei();
	struct CAN_msg r, m;
	delay_mS(1000);
	init_ADC();
	int last_ticks;
	while(1){
		/*if(CAN_msg_available()){
			while(CAN_msg_available()){
				CAN_get_msg(&r);
			}
			int i = *((uint16_t*)&r.data);
			write_PWM(PE4, i);
			tprintf("%d\n", i);
		}
		*/
		if(CAN_msg_available()){
			CAN_get_msg(&r);
			dump_message(r);
		}
		int i = read_ADC(0);//get_encoder_ticks();
	//	if(i < 0){reset_encoder(); i = 0;}
	//	if(i > 1023){set_encoder_ticks(1023); i = 1023;}
		tprintf("%d\n", i);
		*((int*)&m.data) = i;
		m.id = 0;
		m.length = 2;
		m.flags = 0;
		//dump_message(m);
		CAN_send_msg(&m);
		
		delay_mS(100);
	}
}