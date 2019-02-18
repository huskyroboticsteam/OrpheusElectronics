#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
	cli();
	DDRA = 0xF0;
	while(1){
		PORTA ^= 1<<5;
		for(int i = 0;i < 20000;i++){
			asm("nop");
		}
		if(!(PINC & 2)){
			PORTA |= 1<<4;
		} else {
			PORTA &= ~(1<<4);
		}
	}
}