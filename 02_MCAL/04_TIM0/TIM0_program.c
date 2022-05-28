/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01 
* SWC		   :		   TIM0
*/
/* AVR Headers */
#include "avr/interrupt.h"
/* LIB headers */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32A.h"
/* Driver Headers */
#include "TIM0_interface.h"
#include "TIM0_config.h"
#include "TIM0_private.h"

//u8  TIM0_Flag        = 0;
u32 TIM0_TOV_Counter = 0;
void (*TIM0_pcbTOV)(void) = NULL;
void (*TIM0_pcbCTC)(void) = NULL;

/* Fns Implementations */
void TIM0_voidInit(TIM0_Config_t *Copy_pstrTIM0Config){
	/* Setting the mode */
	if(Copy_pstrTIM0Config->Mode == TIM0_NORMAL){
		CLR_BIT(TIM0_TCCR0, 3);
		CLR_BIT(TIM0_TCCR0, 6);
	}//if
	else if(Copy_pstrTIM0Config->Mode == TIM0_PHASE_PWM){
		CLR_BIT(TIM0_TCCR0, 3);
		SET_BIT(TIM0_TCCR0, 6);		
	}//else if
	else if((Copy_pstrTIM0Config->Mode == TIM0_CTC) || (Copy_pstrTIM0Config->Mode == TIM0_NON_PWM)){
		SET_BIT(TIM0_TCCR0, 3);
		CLR_BIT(TIM0_TCCR0, 6);		
	}//else if
	else if(Copy_pstrTIM0Config->Mode == TIM0_FAST_PWM){
		SET_BIT(TIM0_TCCR0, 3);
		SET_BIT(TIM0_TCCR0, 6);		
	}//else if
	else{
		/* Do nothing */
	}//else
	/* Adjust the OC0 Pin */
	TIM0_TCCR0 &= 0xCF;
	if(Copy_pstrTIM0Config->OC0NonPWM != TIM0_OC0_NOT_CONNECTED){
		TIM0_TCCR0 |= Copy_pstrTIM0Config->OC0NonPWM;
	}//if
	else if(Copy_pstrTIM0Config->OC0FastPWM != TIM0_OC0_NOT_CONNECTED){
		TIM0_TCCR0 |= Copy_pstrTIM0Config->OC0FastPWM;
	}//else if
	else if(Copy_pstrTIM0Config->OC0PhasePWM != TIM0_OC0_NOT_CONNECTED){
		TIM0_TCCR0 |= Copy_pstrTIM0Config->OC0PhasePWM;
	}//else if
	else{
		/* Do Nothing */
	}//else
	/* Adjust FOC0 */
	CLR_BIT(TIM0_TCCR0, 7);
	/* Adjust TOV Interrupt */
	if(Copy_pstrTIM0Config->TOVInterrupt == TIM0_TOV_DISABLE){
		CLR_BIT(TIM0_TIMSK, 0);
	}//if
	else{
		SET_BIT(TIM0_TIMSK, 0);
	}//else
	/* Adjust Compare Math Interrupt */
	if(Copy_pstrTIM0Config->TOCInterrupt == TIM0_TOC_DISABLE){
		CLR_BIT(TIM0_TIMSK, 1);
	}//if
	else{
		SET_BIT(TIM0_TIMSK, 1);
	}//else		
	/* Enable the global interrupt */
	SET_BIT(SREG, 7);
}//TIM0_voidInit
void TIM0_voidStart(TIM0_Config_t *Copy_pstrTIM0Config){
	//TIM0_Flag = 0;
	/* Adjust Clock Prescalar */
	TIM0_TCCR0 &= (0xF8);
	TIM0_TCCR0 |= Copy_pstrTIM0Config->Prescalar;	
}//TIM0_voidStart
void TIM0_voidSetTCNT0(u8 Copy_u8InitValue){
	TIM0_TCNT0 = Copy_u8InitValue;
}//TIM0_voidSetTCNT0
u32  TIM0_u32ReadTIM0(void){
	u32 Loc_u32ReturnVal;
	Loc_u32ReturnVal = (TIM0_TOV_Counter * 256) + TIM0_TCNT0;
	return(Loc_u32ReturnVal);
}//TIM0_u32ReadTIM0
void TIM0_voidSetOverflowInterrupt(void (*Copy_pCB)(void)){
	if(Copy_pCB != NULL){
		TIM0_pcbTOV = Copy_pCB;
	}//if
}//TIM0_voidSetOverflowInterrupt
void TIM0_voidSetOCR0(u8 Copy_u8InitValue){
	TIM0_OCR0 = Copy_u8InitValue;
}//TIM0_voidSetOCR0
void TIM0_voidSetCompareInterrupt(void (*Copy_pCB)(void)){
	if(Copy_pCB != NULL){
		TIM0_pcbCTC = Copy_pCB;
	}//if
}//TIM0_voidSetCompareInterrupt
void TIM0_voidStopTIM0(void){
	TIM0_TCCR0 &= (0xF8);
}//TIM0_voidStopTIM0
void TIM0_voidUninit(void){
	TIM0_TCCR0 = 0;
}//TIM0_voidUninit
void TIM0_GenerateFastPWM(TIM0_Config_t *Copy_pstrTIM0Config, u8 Copy_u8DutyCycle){
	u8 Loc_u8OCRValue;
	/* Make OC0 Output */
	SET_BIT(GPIO_DDRB, 3);
	if(Copy_pstrTIM0Config->OC0FastPWM == TIM0_OC0_CLR_COMP){
		Loc_u8OCRValue = ((256 * Copy_u8DutyCycle)/100) - 1;
		TIM0_OCR0 = Loc_u8OCRValue;
	}//if
	else if(Copy_pstrTIM0Config->OC0FastPWM == TIM0_OC0_SET_COMP){
		Loc_u8OCRValue = 255 - ((256 * Copy_u8DutyCycle)/100);
		TIM0_OCR0 = Loc_u8OCRValue;		
	}//else if
	else{
		/* Do Nothing */
	}//else
}//TIM0_GenerateFastPWM
void TIM0_GeneratePhasePWM(TIM0_Config_t *Copy_pstrTIM0Config, u8 Copy_u8DutyCycle){
	u8 Loc_u8OCRValue;
	/* Make OC0 Output */
	SET_BIT(GPIO_DDRB, 3);
	if(Copy_pstrTIM0Config->OC0PhasePWM == TIM0_OC0_SET_DOWNCOUNT){
		Loc_u8OCRValue = (255 * Copy_u8DutyCycle)/100;
		TIM0_OCR0 = Loc_u8OCRValue;
	}//if
	else if(Copy_pstrTIM0Config->OC0PhasePWM == TIM0_OC0_CLR_DOWNCOUNT){
		Loc_u8OCRValue = 255 - ((255 * Copy_u8DutyCycle)/100);
		TIM0_OCR0 = Loc_u8OCRValue;
	}//else if
	else{
		/* Do Nothing */
	}//else
}//TIM0_GeneratePhasePWM
ISR(TIMER0_OVF_vect){
	TIM0_TOV_Counter++;
	if(TIM0_pcbTOV != NULL){
		(*TIM0_pcbTOV)();
	}//if
}//ISR_Timer0_Overflow
ISR(TIMER0_COMP_vect){
	(*TIM0_pcbCTC)();
}//ISR_Timer0_CompareMatch
