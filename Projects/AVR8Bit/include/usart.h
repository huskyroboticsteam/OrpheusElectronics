#ifndef USART_H
#define USART_H

#define TX_BUF_SZ 16
#define RX_BUF_SZ 16

void usart_init(uint16_t baud);
void usart_end();
void usart_write_char(char c);
void usart_write_string(char *s);
int usart_available();

#endif