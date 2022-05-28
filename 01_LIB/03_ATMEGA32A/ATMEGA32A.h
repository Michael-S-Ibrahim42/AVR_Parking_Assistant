/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC          :	 	   ATMEGA32A
*/

/* The header file guard */
#ifndef ATMEGA32A_H
#define ATMEGA32A_H

	/* The GPIO Registers ******************************************************* */        
	#define GPIO_PORTA							*((volatile u8*)(0x3B))	
	#define GPIO_DDRA							*((volatile u8*)(0x3A))
	#define GPIO_PINA							*((const volatile u8*)(0x39))
	#define GPIO_PORTB							*((volatile u8*)(0x38))	
	#define GPIO_DDRB                    	    *((volatile u8*)(0x37))
	#define GPIO_PINB                    	    *((const volatile u8*)(0x36))
	#define GPIO_PORTC							*((volatile u8*)(0x35))	
	#define GPIO_DDRC                    	    *((volatile u8*)(0x34))
	#define GPIO_PINC                    	    *((const volatile u8*)(0x33))
	#define GPIO_PORTD							*((volatile u8*)(0x32))	
	#define GPIO_DDRD                    	    *((volatile u8*)(0x31))
	#define GPIO_PIND                           *((const volatile u8*)(0x30))
	/* ************************************************************************** */
	/* Global Interrupt Register ************************************************ */
	#define INT_SREG	    					*((volatile u8*)(0x5F))
	/* EXTI Registers *********************************************************** */
	#define EXTI_GICR							*((volatile u8*)(0x5B))
	#define EXTI_GIFR							*((volatile u8*)(0x5A))
	#define EXTI_MCUCR							*((volatile u8*)(0x55))
	#define EXTI_MCUCSR							*((volatile u8*)(0x54))
	/* ************************************************************************** */
	/* TIM0 Registers *********************************************************** */
	#define TIM0_OCR0							*((volatile u8*)(0x5C))
	#define TIM0_TIMSK							*((volatile u8*)(0x59))
	#define TIM0_TIFR							*((volatile u8*)(0x58))
	#define TIM0_TCCR0							*((volatile u8*)(0x53))
	#define TIM0_TCNT0							*((volatile u8*)(0x52))
	/* ************************************************************************** */


#endif
