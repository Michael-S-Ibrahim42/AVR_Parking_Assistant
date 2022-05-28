/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :           EXTI
*/
/* Standard Interrupt Library */
#include <avr/interrupt.h>
/* LIB Headers */                                                	
#include "STD_TYPES.h"                                           	
#include "BIT_MATH.h"                                            	
#include "ATMEGA32A.h"
/* EXTI Headers */
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/* Global Fn Pointers */
volatile void (*EXTI_CBFPointer[3])(void) = {NULL, NULL, NULL};

/* Fns Implementation */
void EXTI_voidInit(EXTI_Config_t* Copy_pstrConfig){
	switch(Copy_pstrConfig->InterruptNumber){
		case (EXTI_0):
			/* Set pin direction and Set pull-up resistor */
			CLR_BIT(GPIO_DDRD, 2);
			SET_BIT(GPIO_PORTD, 2);
			/* Setting the sense control */
			EXTI_MCUCR &= ~(0x03);
			EXTI_MCUCR |=  (0x03 & (Copy_pstrConfig->InterruptSenseControl));
			/* Enabling the PIE */
			EXTI_GICR |= (1<<6);
			/* Enabling the GIE */
			INT_SREG |= (1<<7);
			break;
		case (EXTI_1):
			/* Set pin direction and Set pull-up resistor */
			CLR_BIT(GPIO_DDRD, 3);
			SET_BIT(GPIO_PORTD, 3);
			/* Setting the sense control */	
			EXTI_MCUCR &= ~(0x0C);
			EXTI_MCUCR |=  (0x0C & ((Copy_pstrConfig->InterruptSenseControl) << 2));
			/* Enabling the PIE */
			EXTI_GICR |= (1<<7);
			/* Enabling the GIE */
			INT_SREG |= (1<<7);
			break;
		case (EXTI_2):
			/* Set pin direction and Set pull-up resistor */
			CLR_BIT(GPIO_DDRB, 2);
			SET_BIT(GPIO_PORTB, 2);		
			/* Setting the sense control */
			EXTI_MCUCSR &= ~(1<<6);
			EXTI_MCUCSR |= (0x40 & (((Copy_pstrConfig->InterruptSenseControl)&1)<<6));
			/* Enabling the PIE */
			EXTI_GICR |= (1<<5);			
			/* Enabling the GIE */
			INT_SREG |= (1<<7);			
			break;
		default:
			break;
	}//switch
}//EXTI_Init
void EXTI_voidCBFSetter(EXTI_Config_t* Copy_pstrConfig ,void (*Copy_CBFPointer)(void)){
	switch(Copy_pstrConfig->InterruptNumber){
	case (EXTI_0):
		EXTI_CBFPointer[0] = Copy_CBFPointer;
		break;
	case (EXTI_1):
		EXTI_CBFPointer[1] = Copy_CBFPointer;
		break;
	case (EXTI_2):
		EXTI_CBFPointer[2] = Copy_CBFPointer;
		break;
	default:
		break;
	}//switch
}//EXTI_voidCBFSetter
/* ISR Section */
ISR(INT0_vect){
	(*EXTI_CBFPointer[0])();
}//ISR INT0
ISR(INT1_vect){
	(*EXTI_CBFPointer[1])();
}//ISR INT1
ISR(INT2_vect){
	(*EXTI_CBFPointer[2])();
}//ISR INT2
