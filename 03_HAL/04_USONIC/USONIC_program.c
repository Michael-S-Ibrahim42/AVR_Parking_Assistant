/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   USONIC
*/
/* Standard Headers */
#define F_CPU			16000000UL
#include <util/delay.h>
/* LIB Headers */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL Headers */
#include "TIM0_interface.h"
#include "EXTI_interface.h"
#include "GPIO_interface.h"
/* Driver Headers */
#include "USONIC_interface.h"
#include "USONIC_private.h"
#include "USONIC_config.h"

extern u32 TIM0_TOV_Counter;
volatile u8  USONIC_u8EdgeCount = 0;
volatile u32 USONIC_u32Distance = 0;
static u32 Loc_u32TimerTicksNumber;
EXTI_Config_t Loc_strFallingConfig = {EXTI_0, EXTI_FALLING};
EXTI_Config_t Loc_strRisingConfig = {EXTI_0, EXTI_RISING};

/* Fns Implementations */
void USONIC_voidInit(USONIC_Config_t *Copy_pstrConfig){
	GPIO_voidSetPinDirection(Copy_pstrConfig->Port, Copy_pstrConfig->TrigPin, GPIO_OUT_PIN);
	GPIO_voidSetPinDirection(Copy_pstrConfig->Port, Copy_pstrConfig->EchoPin, GPIO_IN_PIN);
	GPIO_voidWritePin(Copy_pstrConfig->Port, Copy_pstrConfig->TrigPin, GPIO_LOW_PIN);
}//USONIC_voidInit
void USONIC_voidTrigUSONIC(USONIC_Config_t *Copy_pstrConfig){
	GPIO_voidWritePin(Copy_pstrConfig->Port, Copy_pstrConfig->TrigPin, GPIO_HIGH_PIN);
	_delay_us(10);
	GPIO_voidWritePin(Copy_pstrConfig->Port, Copy_pstrConfig->TrigPin, GPIO_LOW_PIN);
}//USONIC_voidTrigUSONIC
void USONIC_voidCalcDistance(void){
	USONIC_u8EdgeCount++;
	if(USONIC_u8EdgeCount == 1){
		TIM0_voidSetTCNT0(0);
		TIM0_TOV_Counter = 0;
		EXTI_voidInit(&Loc_strFallingConfig);
	}//if
	else{
		EXTI_voidInit(&Loc_strRisingConfig);
	    USONIC_u8EdgeCount = 0;
		Loc_u32TimerTicksNumber = TIM0_u32ReadTIM0();
		TIM0_voidSetTCNT0(0);
		USONIC_u32Distance = (Loc_u32TimerTicksNumber * 0.008575);  
	}//else
}//USONIC_voidCalcDistance
