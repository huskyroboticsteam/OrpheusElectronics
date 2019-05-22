/*
 * PowerDistBasic.c
 *
 * Created: 21-May-19 18:18:55
 * Author : Akkshaj Singh (AJ)
 * Basic Power Distro Port Setup
 */ 

#include <avr/io.h>

void init(){
	
	PORTC = 0b00000000;
	DDRC = 0b11100000;
	
}

int main(void)
{
    init();
	
    while (1) 
    {
    }
}

