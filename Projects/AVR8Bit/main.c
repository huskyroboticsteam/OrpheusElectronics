#include "conf.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "pwm.h"
#include "motors.h"
#include "timers.h"
#include "adc.h"
#include "can.h"
#include "usart.h"

int main(){
	wdt_enable(WDTO_1S);
	setup_timers();
	init_motor();
	init_ADC();
	init_CAN(CAN_250_BAUD, 4);
	
	while(1){
		motor_control_tick();
		wdt_reset();
	}
}