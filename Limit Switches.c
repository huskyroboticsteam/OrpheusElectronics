#include "stm32f3xx.h"  

#define Limit_Switch_Start  GPIO_PIN_1
#define Limit_Switch_End    GPIO_PIN_2

void Limit_Switch_Init(void)
{
		G
	
	
	
}


void limit_switch_1_interrupt_handler(void)
	{
			if(HAL_GPIO_ReadPin( /* limit switch 1 pin */ )){
				
				// if the limit switch variable == 1
				if(limit_switch_1)
				{
					// do nothing?
				} 
				// if the limit switch variable == 0
				else if (!limit_switch_1)
				{
					// Flag limit switch variable as 1
					limit_switch_1 = 1;
				}
			
		// Device header
		HAL_GPIO_EXTI_IRQHandler( /* limit switch 1 pin */ );
	}
	
void limit_switch_2_interrupt handler(void)
	{
			if(HAL_GPIO_ReadPin( /* limit switch 2 pin */ )){
				
				// if the limit switch variable == 1
				if(limit_switch_2)
				{
					// do nothing?
				} 
				// if the limit switch variable == 0
				else if (!limit_switch_2)
				{
					// Flag limit switch variable as 1
					limit_switch_2 = 1;
				}
			
		// Device header
		HAL_GPIO_EXTI_IRQHandler( /* limit switch pin */ );
	}
	
	