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

//#define DEFAULT_Kp_1 140 //Default Kp for position PID
//#define DEFAULT_Ki_1 20  //Default Ki for position PID
//#define DEFAULT_Kd_1 100 //Default Kd for position PID

void set_motor_reverse(uint8_t r);


/*int main(){
	DDRB = 1<<PB6;
	PORTB = 1<<PB6;
	//setup_timers();
	//DDRC = 1;
	//PORTC = 1;
	while(1);
}*/

//#if 0
int main(){
	struct CAN_msg m;
	uint32_t mS;
	DDRA = 0xF0;
	PORTA = 0xF0;
	//DDRC = 1<<3; //Laser
	//DDRC = 2;
	//PORTC = 0;
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
	//wdt_enable(WDTO_2S);
	init_motor();
	if(my_address == 0x12){
		set_motor_reverse(1);
	}
	//set_motor_mode(MOTOR_MODE_PID);
	//enable_motor();
	set_LED(3, 3);
	//PORTE |= (1<<PE4);
	set_Kp(120, 0);
	set_Ki(20, 0);
	set_Kd(170, 0);
	delay_mS(500);
	set_LED(0, 0);
	set_LED(1, 0);
	set_LED(3, 0);
	long last = 0;
	if(my_address == 0x16){
		init_servo();
		set_servo_position(0);
	}
	//PORTC |= 1<<3; //Laser
	//set_motor_mode(MOTOR_MODE_ENABLED);
	int d = 10, inc = 1;
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
			//if(get_encoder_ticks() != last){
			//	tprintf("%d\n", get_encoder_ticks());
			//	last = get_encoder_ticks();
			//}
			if(mS % 100 == 0)
				tprintf("%dmV %dmA\n", get_voltage(), get_motor_current());
		}
		//if(mS % 100 == 0)
//			tprintf("%dmV %dmA\n", get_voltage(), get_motor_current());
		//set_motor_power_raw(300);
		motor_control_tick();
		wdt_reset();
	}
}
//#endif