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
#include "servo.h"
#include "usart.h"
#include "bss.h"

//#define DEFAULT_Kp_1 140 //Default Kp for position PID
//#define DEFAULT_Ki_1 20  //Default Ki for position PID
//#define DEFAULT_Kd_1 100 //Default Kd for position PID

/*int main(){
	DDRE = 1<<PB3;
	PORTE = 1<<PB3;
	//setup_timers();
	//DDRC = 1;
	//PORTC = 1;
	while(1);
}
*/
//#if 0
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
	do_board_specific_setup(my_address);
	wdt_enable(WDTO_2S);
	init_motor();
	//enable_motor();
	delay_mS(500);
	set_LED(0, 0);
	set_LED(1, 0);
	set_LED(3, 0);
	//long last = 0;
	//int d = 10, inc = 1;
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
				tprintf("%dmV %dmA\n", get_voltage(), get_motor_current());
			}
			if(get_motor_mode() & MOTOR_MODE_ENABLED){
				set_LED(2, 3);
				set_LED(1, 0);
				} else {
				set_LED(1, 3);
				set_LED(2, 0);
			}
			//if(get_encoder_ticks() != last){
			//	tprintf("%d\n", get_encoder_ticks());
			//	last = get_encoder_ticks();
			//}
				
		}
		//if(mS % 100 == 0)
//			tprintf("%dmV %dmA\n", get_voltage(), get_motor_current());
		motor_control_tick();
		/*if(get_mS() % 5000 == 0){
			set_servo_position(179);
			DDRC |= 2;
			delay_mS(500);
			set_servo_position(0);
			DDRC &= ~2;
		}*/
		wdt_reset();
	}
}
//#endif