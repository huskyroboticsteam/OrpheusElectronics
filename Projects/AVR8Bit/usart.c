#include "conf.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

char tx_buf[TX_BUF_SZ];
char rx_buf[RX_BUF_SZ];

uint8_t tx_buf_head, tx_buf_tail;
uint8_t rx_buf_head, rx_buf_tail;
uint8_t rx_av;

/*Initialize the USART0
Parameters:
uint16_t baud: The baud rate to use
*/
void usart_init(uint16_t baud){
	tx_buf_head = rx_buf_head = 0;
	tx_buf_tail = rx_buf_tail = 0;
	rx_av = 0;
	UBRR0 = (uint16_t)((F_CPU/16L)/baud)-1;
	UCSR0C = 0x04; //8-bit, 1 stop bit, no parity
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<UDRIE0); //Enable recieve, transmit and interrupts
}

/*Disables USART*/
void usart_end(){
	UCSR0B = 0;
}

/*Writes one character to the USART
Parameters:
char c: the character to write*/
void usart_write_char(char c){
	UCSR0B |= (1<<UDRIE0); //Make sure TX interrupt is enabled
	/*if((tx_buf_tail+1)%TX_BUF_SZ == tx_buf_head){
		return; //No more room
	}*/
	/*No more room. Block until we can put it in the buffer*/
	while((tx_buf_tail+1)%TX_BUF_SZ == tx_buf_head);
	
	tx_buf[tx_buf_tail++] = c;
	if(tx_buf_tail >= TX_BUF_SZ){
		tx_buf_tail = 0;
	}
}

/*Writes a string to the USART
Parameters:
char *s: The string to write*/
void usart_write_string(char *s){
	int i;
	for(i = 0;s[i];i++){
		usart_write_char(s[i]);
	}
}

/*Reads one character (byte) from the USART recieve buffer. If the buffer is empty, it returns 0*/
char usart_read_char(){
	if(!rx_av){
		return 0; //Buffer empty
	}
	char c = rx_buf[rx_buf_head++];
	if(rx_buf_head >= RX_BUF_SZ){
		rx_buf_head = 0;
	}
	rx_av--;
	return c;
}

/*Returns the number of bytes waiting in the USART receive buffer*/
int usart_available(){
	return rx_av;
}

ISR(USART0_RX_vect){ //A byte received
	if((rx_buf_tail+1)%RX_BUF_SZ == rx_buf_head){
		return; //No more room
	}
	rx_buf[rx_buf_tail++] = UDR0;
	rx_av++;
	if(rx_buf_tail >= RX_BUF_SZ){
		rx_buf_tail = 0;
	}
}

ISR(USART0_UDRE_vect){ //AVR's transmit buffer is empty
	if(tx_buf_head == tx_buf_tail){ //Buffer empty
		UCSR0B &= ~(1<<UDRIE0); //Disable interrupt to avoid infinite loop
		return;
	}
	UDR0 = tx_buf[tx_buf_head++];
	if(tx_buf_head >= TX_BUF_SZ){
		tx_buf_head = 0;
	}
}