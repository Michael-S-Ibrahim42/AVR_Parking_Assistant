/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :           EXTI
*/
/* The header file guard */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
	/* MACROS */
	/* Interrupt Number */
	#define EXTI_0							0
	#define EXTI_1							1
	#define EXTI_2							2
	/* Interrupt Sense Control */
	#define EXTI_FALLING					2
	#define EXTI_RISING						3
	/* EXTI Config type */
	typedef struct{
		u8 InterruptNumber;
		u8 InterruptSenseControl;
	}EXTI_Config_t;
	/* Fns Prototypes */
	void EXTI_voidInit(EXTI_Config_t* Copy_pstrConfig);
	void EXTI_voidCBFSetter(EXTI_Config_t* Copy_pstrConfig ,void (*Copy_CBFPointer)(void));
	
#endif
