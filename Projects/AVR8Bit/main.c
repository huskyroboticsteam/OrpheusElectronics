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
#include "messaging.h"
#include "can.h"
#include "util.h"
#include "usart.h"

int main(){
	struct CAN_msg m;
	uint32_t mS;
	DDRA = 0xF0;
	PORTA = 0xF0;
	setup_timers();
	_delay_ms(100);
	PORTA = 0;
	set_LED(0, 3);
	sei();
	usart_init(19200); //Debug serial
	set_LED(1, 3);
	delay_mS(666); //Delay so one can connect to debug serial
	uint16_t my_address = 0x10 | get_dip_switch();
	tprintf("adr=%X\n", my_address);
	delay_mS(250);
	CAN_set_RX_filter(0x1F, my_address);
	init_CAN(CAN_125_BAUD, 4, 0);
	set_LED(2, 3);
	init_encoder();
	init_ADC();
	wdt_enable(WDTO_2S);
	init_motor();
	set_motor_mode(MOTOR_MODE_PID);
	//enable_motor();
	set_LED(3, 3);
	//PORTE |= (1<<PE4);
	set_Kp(0, 7);
	set_Ki(0, 3);
	set_Kd(0, 1);
	delay_mS(500);
	set_LED(0, 0);
	set_LED(1, 0);
	set_LED(3, 0);
	while(1){
		mS = get_mS();
		if(!PID_due){ //Don't busy the processor if the PID is due to run
			if(CAN_msg_available()){
				set_LED(3, 3);
				update_LEDS(get_mS()/40);
				CAN_get_msg(&m);
				handle_CAN_message(&m);
				set_LED(3, 0);
			}
			if(mS % 256 == 0){
				send_encoder_count(); //Send encoder count 4 times per second
			}
			if(mS % 512 == 0){
				send_telemetry(); //Send encoder count 2 times per second
			}
			if(get_motor_mode() & MOTOR_MODE_ENABLED){
				set_LED(2, 3);
				set_LED(1, 0);
			} else {
				set_LED(1, 3);
				set_LED(2, 0);
			}
		}
		motor_control_tick();
		wdt_reset();
	}
}