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
	setup_timers();
	set_LED(0, 2);
	usart_init(19200); //Debug serial
	_delay_ms(666); //Delay so one can connect to debug serial
	sei();
	init_CAN(CAN_100_BAUD, 4, 0);
	init_encoder();
	init_motor();
	set_motor_mode(MOTOR_MODE_PID);
	enable_motor();
	PORTE = 0;
	set_LED(0, 3);
	while(1){
		mS = get_mS();
		if(!PID_due){ //Don't busy the processor if the PID is due to run
			if(CAN_msg_available()){
				CAN_get_msg(&m);
				handle_CAN_message(&m);
			}
			if(mS % 256 == 0){
				send_encoder_count(); //Send encoder count 4 times per second
			}
			if(mS % 512 == 0){
				send_telemetry(); //Send encoder count 2 times per second
			}
		}
		motor_control_tick();
	}
}