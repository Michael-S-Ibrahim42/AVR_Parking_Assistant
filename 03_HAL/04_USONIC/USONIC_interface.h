/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   USONIC
*/

/* The header file guard */
#ifndef USONIC_INTERFACE_H
#define USONIC_INTERFACE_H


	typedef struct{
		u8 Port;
		u8 TrigPin;
		u8 EchoPin;
	}USONIC_Config_t;
	
	/* Fns Prototypes */
	void USONIC_voidInit(USONIC_Config_t *Copy_pstrConfig);
	void USONIC_voidTrigUSONIC(USONIC_Config_t *Copy_pstrConfig);
	void USONIC_voidCalcDistance(void);
	
#endif
