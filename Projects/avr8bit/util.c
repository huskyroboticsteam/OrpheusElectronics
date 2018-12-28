#include <avr/io.h>
#include "usart.h"
#include "util.h"

uint8_t LED_states;

int16_t min(int16_t a, int16_t b){
	return (a < b)? a:b;
}

int16_t max(int16_t a, int16_t b){
	return (a > b)? a:b;
}

/*Sets the mode of the debug LEDs
Parameters:
uint8_t L: the number of the LED to set (0-3)
uint8_t state: the mode for the LED:
	0 -> Off
	1 -> Slow flashing
	2 -> Quick flashing
	3 -> Steady on
*/
void set_LED(uint8_t L, uint8_t state){
	if(L > 4 || state > 3) return;
	if(state){
		state = 4 - state;
	}
	LED_states = (LED_states & ~(3 << L)) | (state << L);
}

/*Integer implementation of abs()*/
uint16_t int_abs(int16_t x){
	return x<0? -x: x;
}

/*Call this from a timer interrupt to update the debug LEDs
Parameters:
uint16_t count: The timer count
*/
void inline update_LEDS(uint16_t count){
	int i;
	uint8_t v;
	if(!LED_states) return;
	for(i = 0;i < 4;i++){
		v = (i >> (2*i)) & 3;
		if(v == 0 || count % v){
			PORTA &= ~(1 << (i+4));
		} else {
			PORTA |= 1 << (i+4);
		}
	}
}

/*Reads a string from uart
Parameters:
char *buffer: the buffer to put the string
char until: The deliminating character
*/
void read_string(char *buffer, char until){
	char c = -1;
	int i = 0;
	while(c != until){
		c = usart_read_char();
		tprintf("%c", c);
		buffer[i++] = c;
	}
	buffer[i-1] = 0;
}
