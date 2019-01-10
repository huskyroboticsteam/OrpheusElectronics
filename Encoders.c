// Quadrature Encoder C file

/*--------------------------------------------------------------

 1) Add line to main.c inside main function

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);

 2) Inside SysTick_Hanlder

	call encoderRead()

---------------------------------------------------------------*/

// Header file initialization
#include "stm32f3xx.h"
#include "main.h"
#include "stm32f3xx_hal.h"

/*	Variables */
volatile uint32_t newEncoderCount;
volatile uint32_t deltaCount;

/*	Private Variables */
static volatile uint32_t oldEncoderCount;

/* Extern Variables */
extern uint32_t timeConstant;

TIM_HandleTypeDef htim2;


void Encoder_Init(void)
{
	// ------------ Initialize Encoder GPIOs --------------------
	GPIO_InitTypeDef GPIO_Encoder_InitStruct
	GPIO_Encoder_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1
	GPIO_Encoder_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_Encoder_InitStruct.Pull = GPIO_PULLUP;
	GPIO_Encoder_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_Encoder_InitStruct.Alternate = GPIO_AF1_TIM2
	HAL_GPIO_Init(GPIOA, &GPIO_Encoder_InitStruct);

	TIM_Encoder_InitTypeDef encoder;
	TIM_MasterConfigTypeDef sMasterConfig;

	// Encoder Timer Settings
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 5000;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// Encoder Mode Settings
	encoder.EncoderMode = TIM_ENCODERMODE_TI12;
	encoder.IC1Polarity = TIM_ICPOLARITY_RISING;
	encoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	encoder.IC1Prescaler = TIM_ICPSC_DIV1;
	encoder.IC1Filter = 0;
	encoder.IC2Polarity = TIM_ICPOLARITY_RISING;
	encoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	encoder.IC2Prescaler = TIM_ICPSC_DIV1;
	encoder.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim2, &encoder) != HAL_OK)
	{
	_Error_Handler(__FILE__, __LINE__);
	}

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }
}

void encoderRead()
{
	// Update old encoder count
	oldEncoderCount = newEncoderCount;

	// Get new encoder count
	newEncoderCount = TIM2->CNT;

	// Get change in the position
	deltaCount = newEncoderCount - oldEncoderCount;

	// Obtain speed of the encoder/motor
	speed = deltaCount/timeConstant;
}
