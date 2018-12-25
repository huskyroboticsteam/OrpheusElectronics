#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_PWM_PORT PORTE
#define MOTOR_PWM_DDR DDRE
#define MOTOR_PWM PE3
#define MOTOR_DIR_PORT PORTE
#define MOTOR_DIR_DDR DDRE
#define MOTOR_DIR PE2
#define MOTOR_CS_DDR DDRF
#define MOTOR_CS 0

#define MOTOR_MODE_PID 2
#define MOTOR_MODE_ENABLED 1

void init_motor();
uint8_t PID_due();
void set_motor_power(int16_t power);
uint16_t get_motor_current();
uint8_t check_motor_stall();
void enable_motor();
void disable_motor();
uint8_t get_motor_mode();
void set_motor_mode(uint8_t mode);
void set_target_position(int32_t position);
void set_target_velocity(uint16_t velocity);
int16_t get_motor_velocity();
int32_t get_target_position();
int32_t get_target_velocity();
void motor_control_tick();
uint8_t get_motor_limit_switch_state();

#endif