#include <avr/io.h>
#include "conf.h"
#include "timers.h"
#include "pwm.h"
#include "adc.h"
#include "encoder.h"
#include "motor.h"

int32_t motor_target_pos; //Motor target position
int16_t motor_target_vel; //Motor target velocity
int32_t motor_max_pos;
int32_t motor_last_pos;
int16_t motor_vel;
uint32_t motor_last_timestamp;
uint8_t motor_mode;

/*Initalizes the motor controller*/
void init_motor(){
	/*Turn off the PWM pin and set it to output*/
	MOTOR_PWM_PORT &= ~(1<<MOTOR_PWM);
	MOTOR_PWM_DDR |= (1<<MOTOR_PWM);
	/*Set direction pin to output and set motor direction to forward*/
	MOTOR_DIR_DDR |= (1<<MOTOR_DIR);
	MOTOR_DIR_PORT |= (1<<MOTOR_DIR);
	/*Set current sense pin to input*/
	MOTOR_CS_DDR &= ~(1<<MOTOR_CS);
	
	motor_target_pos = motor_target_vel = 0;
	init_encoder();
	motor_last_post = 0;
	motor_last_timestamp = getmS();
}

/*Sets the motor power
  Parameters:
  int16_t power: the motor power to set -1023 to +1023
  Negative values reverse the motor
*/
void set_motor_power(int16_t power){
	if(power > 1023) power = 1023;
	if(power < -1023) power = -1023;
	if(power == 0 || !(motor_mode & MOTOR_MODE_ENABLED)){
		write_PWM(MOTOR_PWM, 0);
		MOTOR_PWM_PORT &= (1<<MOTOR_PWM);
		return;
	}
	if(power < 0){
		if(MOTOR_DIR_PORT & (1<<MOTOR_DIR)){
			write_PWM(MOTOR_PWM, 0); //Turn off PWM first if we are changing direction
			MOTOR_DIR_PORT &= ~(1<<MOTOR_DIR); //Reverse
		}
		power = -power;
	} else {
		if(!(MOTOR_DIR_PORT & (1<<MOTOR_DIR))){
			write_PWM(MOTOR_PWM, 0);
			MOTOR_DIR_PORT |= (1<<MOTOR_DIR); //Forward
		}
	}
	write_PWM(MOTOR_PWM, power);
}

/*Returns the motor current in milliamps*/
uint16_t get_motor_current(){
	uint16_t val = read_ADC(MOTOR_CS);
	#ifdef FIVE_VOLTS
	/*4.883 mV/unit*/
	if(val < 10) return 0;
	val -= 10; //Remove 50mV offset
	val = (val * 122) + (val/11); //Convert to mA
	#else //3.3V
	/*3.22 mV/unit*/
	if(val < 16) return 0;
	val -= 16; //Remove 50mV offset
	val = (val << 6) + (val << 4) + (val >> 1); //Fast multiply by 80.5
	#endif
	return val;
}
uint8_t check_motor_stall(){
	/*Check motor current*/
	/*Check derrivative of encoder?*/
	return 0;
}
void set_target_position(int32_t position){
	if(position < 0 || position > motor_max_position) return;
	motor_target_pos = position;
}
void set_target_velocity(uint16_t velocity){
	motor_target_vel = velocity;
}
int32_t get_target_position(){
	return motor_target_pos;
}
int32_t get_target_velocity(){
	return motor_target_vel;
}
int16_t get_motor_velocity(){
	int32_t enc = get_encoder_position();
	int32_t mS = get_mS();
	if(mS - last_motor_timestamp < 50){ //Has enough time passed?
		return motor_vel; //No. Return the old value
	} else {
		int16_t new_velocity = (1000*(enc - motor_last_pos))/(mS - motor_last_timestamp); //Calculate the new velocity
		motor_vel = motor_vel/2 + new_velocity/2; //Low-pass filter
		motor_last_pos = enc; //Update values
		motor_last_timestamp = mS;
		return motor_vel;
	}
}
void motor_control_tick(){
	if(motor_mode & MOTOR_MODE_VELOCITY){
	}
	if(motor_mode & MOTOR_MODE_POSITION){
		int pos = get_motor_position();
	}
	uint8_t limit_sw = get_motor_limit_switch_state();
	if(limit_sw & 1){
		reset_encoder();
		set_motor_power(0);
	}
	if(limit_sw & 2){
		motor_max_position = get_encoder_ticks();
		if(motor_target_pos > motor_max_position){
			motor_target_pos = motor_max_position;
		}
		set_motor_power(0);
	}
}
void enable_motor(){
	motor_mode |= MOTOR_MODE_ENABLED;
}
void disable_motor(){
	set_motor_power(0);
	motor_mode &= ~MOTOR_MODE_ENABLED;
}
void set_motor_mode(uint8_t mode){
	motor_mode = mode;
}
uint8_t get_motor_mode(){
	return motor_mode;
}
uint8_t get_motor_limit_switch_state(){
	return 0; //Get GPIO data
}