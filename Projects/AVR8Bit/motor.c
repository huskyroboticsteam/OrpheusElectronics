#include <avr/io.h>
#include "conf.h"
#include "timers.h"
#include "pwm.h"
#include "adc.h"
#include "encoder.h"
#include "motor.h"

int32_t motor_target_pos; //Motor target position
int16_t motor_target_vel; //Motor target velocity
int32_t motor_max_pos; //The maximum position of the motor
int32_t last_pos_err;
int16_t last_vel_err;
int32_t pos_i,vel_i;
int16_t motor_power;

uint32_t last_mS;

uint8_t motor_mode; //Traxcks the motor mode

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
//	motor_last_pos = 0;
//	motor_last_timestamp = get_mS();
}

/*Returns true if the PID loop is due to run*/
uint8_t PID_due(){
	if(get_mS() - last_mS > 49){
		return 1;
	}
	return 0;
}

/*Sets the motor power
  Parameters:
  int16_t power: the motor power to set -1023 to +1023
  Negative values reverse the motor
*/
void set_motor_power(int16_t power){
	#if 0
	if(power > 1023) power = 1023;
	if(power < -1023) power = -1023;
	if(power == 0 || !(motor_mode & MOTOR_MODE_ENABLED)){ //Shut down the motor if it isn't enabled or power is 0
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
	#endif
	if(power > 1023) power = 1023;
	if(power < -1023) power = -1023;
	if(power > 0){
		write_PWM(PE3, 0);
		write_PWM(PE4, power);
	} else {
		write_PWM(PE4, 0);
		write_PWM(PE3, -power);
	}
}

/*Returns the motor current in milliamps*/
uint16_t get_motor_current(){
	internalAREF();
	uint16_t val = read_ADC(MOTOR_CS);
	//ADMUX &= 0xC0;
	//delay_mS(5);
	//2.5 mV/unit. 8 Units/Amp
	if(val < 20) return 0;
	val -= 20; //Remove 50mV offset;
	val <<= 8; //Multiply by 128
	return val;
}

/*Returns true if the motor is stalled*/
uint8_t check_motor_stall(){
	return get_motor_current() > 5000;
	/*Check motor current*/
	/*Check derrivative of encoder?*/
	//return 0;
}

/*Sets a target position for the motor*/
void set_target_position(int32_t position){
	if(position < 0 || position > motor_max_pos) return;
	motor_target_pos = position;
}

/*Sets a target velocity for the motor*/
void set_target_velocity(uint16_t velocity){
	motor_target_vel = velocity;
}

/*Gets the target position for the motor*/
int32_t get_target_position(){
	return motor_target_pos;
}

/*Gets the target velocity for the motor*/
int32_t get_target_velocity(){
	return motor_target_vel;
}

/*Gets the current motor velocity*/
int16_t get_motor_velocity(){
	return get_encoder_velocity();
}

/*Executes one tick of the motor control system. Call this in a loop!*/
void motor_control_tick(){
	if(check_motor_stall()){
		motor_power = 0;
		disable_motor();
		/*Send CAN message*/
	}
	uint8_t limit_sw = get_motor_limit_switch_state();
	if(limit_sw & 1){
		reset_encoder();
		motor_power = 0;
		set_motor_power(0);
	}
	if(limit_sw & 2){
		motor_max_pos = get_encoder_ticks();
		if(motor_target_pos > motor_max_pos){
			motor_target_pos = motor_max_pos;
		}
		motor_power = 0;
		set_motor_power(0);
	}
	if(motor_mode & MOTOR_MODE_PID && PID_due()){
		int32_t pos = get_encoder_ticks();
		int32_t errorp = pos - motor_target_pos;
		int32_t dp = errorp - last_pos_err;
		uint16_t mpp = errorp*1 + dp*1 + pos_i*1;
		pos_i += errorp;
		if(pos_i > 16384) pos_i = 16384;
		if(pos_i < -16384) pos_i = -16384;
		
		int16_t vel = get_motor_velocity();
		int16_t errorv = vel - motor_target_vel;
		int16_t dv = errorv - last_vel_err;
		uint16_t mvp = errorv*1 + dv*1 + vel_i*1;
		vel_i += errorv;
		if(vel_i > 16384) vel_i = 16384;
		if(vel_i < -16384) vel_i = -16384;
		
		if(errorp > 1000){
			motor_power = mvp;
		} else {
			motor_power = mpp;
		}		
		last_mS = get_mS();
	}
	set_motor_power(motor_power);		
}

/*Enables the motor*/
void enable_motor(){
	motor_mode |= MOTOR_MODE_ENABLED;
}

/*Disables the motor*/
void disable_motor(){
	set_motor_power(0);
	motor_mode &= ~MOTOR_MODE_ENABLED;
}

/*Sets the motor mode*/
void set_motor_mode(uint8_t mode){
	motor_mode = mode;
}

/*Gets the motor mode*/
uint8_t get_motor_mode(){
	return motor_mode;
}

/*Gets the state of the limit switches*/
uint8_t get_motor_limit_switch_state(){
	return (PINE & 0xC0) >> 6; //Get GPIO data
}