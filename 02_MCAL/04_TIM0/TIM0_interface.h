/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   TIM0
*/
/* The header file guard */
#ifndef TIM0_INTERFACE_H
#define TIM0_INTERFACE_H
	/* TIM0 Prescalars */
	#define TIM0_CLK_1							0x1
	#define TIM0_CLK_8							0x2
	#define TIM0_CLK_64							0x3
	#define TIM0_CLK_256						0x4
	#define TIM0_CLK_1024						0x5
	#define TIM0_CLK_EXT_FALLING				0x6
	#define TIM0_CLK_EXT_RISING					0x7
	/* TIM0 Moder Options */
	#define TIM0_NORMAL							0x0
	#define TIM0_PHASE_PWM						0x1
	#define TIM0_CTC							0x2
	#define TIM0_FAST_PWM						0x3
	#define TIM0_NON_PWM						0x4
	/* OC0 Pin States */
	#define TIM0_OC0_NOT_CONNECTED				0x00
	/* Non-PWM Modes */
	#define TIM0_TOG_OC0_COMP					0x10
	#define TIM0_CLR_OC0_COMP					0x20
	#define TIM0_SET_OC0_COMP					0x30
	/* Fast-PWM Modes */
	#define TIM0_OC0_CLR_COMP					0x20	
	#define TIM0_OC0_SET_COMP					0x30
	/* Phase-PWM */
	#define TIM0_OC0_SET_DOWNCOUNT				0x20
	#define TIM0_OC0_CLR_DOWNCOUNT				0x30
	/* TIM0 Overflow interrupt */
	#define TIM0_TOV_DISABLE					0
	#define TIM0_TOV_ENABLE						1
	/* TIM0 Compare Match Interrupt */
	#define TIM0_TOC_DISABLE					0
	#define TIM0_TOC_ENABLE						1
	
	/* Defining the timer configurations */
	typedef struct{
		u8 Mode;
		u8 OC0NonPWM;
		u8 OC0FastPWM;
		u8 OC0PhasePWM;
		u8 TOVInterrupt;
		u8 TOCInterrupt;
		u8 Prescalar;
	}TIM0_Config_t;
	
	/* Fns Prototypes */
	void TIM0_voidInit(TIM0_Config_t *Copy_pstrTIM0Config);
	void TIM0_voidStart(TIM0_Config_t *Copy_pstrTIM0Config);
	void TIM0_voidSetTCNT0(u8 Copy_u8InitValue);
	u32  TIM0_u32ReadTIM0(void);
	void TIM0_voidSetOverflowInterrupt(void (*Copy_pCB)(void));
	void TIM0_voidSetOCR0(u8 Copy_u8InitValue);
	void TIM0_voidSetCompareInterrupt(void (*Copy_pCB)(void));
	void TIM0_voidStopTIM0(void);
	void TIM0_voidUninit(void);
	void TIM0_GenerateFastPWM(TIM0_Config_t *Copy_pstrTIM0Config, u8 Copy_u8DutyCycle);
	void TIM0_GeneratePhasePWM(TIM0_Config_t *Copy_pstrTIM0Config, u8 Copy_u8DutyCycle);
	
#endif