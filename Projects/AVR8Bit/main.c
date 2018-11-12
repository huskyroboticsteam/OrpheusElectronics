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
	init_encoder();
	sei();
	while(1){
		uint16_t ec = get_encoder_ticks();
		tprintf("%d\n", ec); 
		delay_mS(100);
	}
}