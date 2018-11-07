#include <avr/io.h>
#include "adc.h"
#include "conf.h"

/*Initialize the ADC and prepare it for reading*/
void init_ADC(){
	ADMUX = 0; //Clear the ADC MUX
	#if F_CPU < 10000000
	ADCSRA = (1<<ADPS2) | (1<<ADPS0); //Up to 10MHz, prescale by 32
	#else
	ADCSRA = (1<<ADPS2) | (1<<ADPS1); //For faster clocks, prescale by 64
	#endif
	ADCSRA |= (1<<ADEN); //Enable the ADC
}

/*Reads one sample from the ADC and returns it
  Paramters:
  uint8_t pin: The ADC pin number to read
  Return value:
  The 10-bit ADC result
*/
uint16_t read_ADC(uint8_t pin){
	uint8_t l,h;
	ADMUX = (ADMUX & 0xC0) | pin & 7; //Setup ADC, preserve REFS0
	ADCSRA |= (1<<ADSC); //Start the conversion
	while(ADCSRA & (1<<ADSC)); //Wait for conversion
	l = ADCL;  //Read and return 10 bit result
	h = ADCH;
	return (h << 8)|l; 
}