#ifndef CAN_H
#define CAN_H

#define CAN_1000_BAUD 0x000412
#define CAN_500_BAUD 0x000C36
#define CAN_250_BAUD 0x020C37
#define CAN_125_BAUD 0x060C37
#define CAN_100_BAUD 0x080C37

struct CAN_msg {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
};

void init_CAN(uint32_t rate, uint8_t txmobs);
void select_mob(uint8_t mob);
uint8_t CAN_msg_available();
void CAN_get_msg(struct CAN_msg *buf);
uint8_t CAN_send_msg(struct CAN_msg *buf);

#endif