/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   Parking Assistant / Anti Crashing
*/
/* RTOS Headers */
#include "FREERTOS.h"
#include "task.h"
#include "event_groups.h"
/* LIB Headers */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/* MCAL Headers */
#include "GPIO_interface.h"
#include "EXTI_interface.h"
#include "TIM0_interface.h"
/* HAL Headers */
#include "BUZZER_interface.h"
#include "LCD_interface.h"
#include "USONIC_interface.h"
/* LCD MACROS */
#define LCD_REV_L0			(u8*)"    *REVERSE*   "
#define LCD_REV_L1			(u8*)"Distance=       "
#define LCD_REV_DIGIT		9
#define LCD_FOR_L0			(u8*)"    *FORWARD*   "
#define LCD_FOR_L1			(u8*)"                "
#define LCD_WARN_L0			(u8*)"   **WARNING**  "
#define LCD_WARN_L1			(u8*)"Distance=       "
#define LCD_WARN_DIGIT		9
#define LCD_ALARM_L0		(u8*)"  !!!CRASH!!!   "
#define LCD_ALARM_L1		(u8*)"  !!!CRASH!!!   "
/* Event Bits */
#define E_ALARM				(1<<0)
#define E_LCD_SCREEN		(1<<1)
#define E_LCD_DISTANCE		(1<<2)
/* Defined Types */
typedef enum{
	SS_REVERSE,
	SS_FORWARD,
	SS_WARN,
	SS_ALARM
}SystemState_t;
typedef struct{
	SystemState_t SysState;
}System_t;
/* Tasks Prototypes */
void T_Display		(void* pvData);
void T_Alarm		(void* pvData);
void T_DistanceCheck(void* pvData);
/* Fns Prototypes */
void PA_voidInitSys(void);
/* Global Variables */
USONIC_Config_t PA_strUSONIC = {GPIO_D, GPIO_PIN1, GPIO_PIN2};
extern volatile u32 USONIC_u32Distance;
System_t ParkingAssistance = {SS_FORWARD};
EventGroupHandle_t paEventGroup = NULL;
/* CallBack Fns Prototypes */
void PA_voidSetReverseState(void);
void PA_voidSetForwardState(void);
/* main Definition */
int main(void){
	PA_voidInitSys();
	paEventGroup = xEventGroupCreate();
	xTaskCreate(T_Alarm        , NULL, 100, NULL, 3, NULL);
	xTaskCreate(T_Display      , NULL, 100, NULL, 2, NULL);
	xTaskCreate(T_DistanceCheck, NULL, 100, NULL, 1, NULL);
	xEventGroupSetBits(paEventGroup, (E_LCD_SCREEN));
	vTaskStartScheduler();
	return(0);
}//main
/* Tasks Definition */
void T_Display(void* pvData){
	EventBits_t egBits = NULL;
	while(1){
		egBits = xEventGroupWaitBits(paEventGroup, (E_LCD_DISTANCE | E_LCD_SCREEN), 1, 0, portMAX_DELAY);
		if(egBits & E_LCD_SCREEN){
			switch(ParkingAssistance.SysState){
			case (SS_FORWARD):
				LCD_SendStringXY(LCD_FOR_L0, 0, 0);
			    LCD_SendStringXY(LCD_FOR_L1, 1, 0);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN1, GPIO_LOW_PIN);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN3, GPIO_LOW_PIN);
				break;
			case (SS_REVERSE):
				LCD_SendStringXY(LCD_REV_L0, 0, 0);
			    LCD_SendStringXY(LCD_REV_L1, 1, 0);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN1, GPIO_LOW_PIN);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN3, GPIO_LOW_PIN);
				break;
			case (SS_WARN):
				LCD_SendStringXY(LCD_WARN_L0, 0, 0);
			    LCD_SendStringXY(LCD_WARN_L1, 1, 0);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN3, GPIO_HIGH_PIN);
				GPIO_voidWritePin(GPIO_B, GPIO_PIN1, GPIO_LOW_PIN);
				break;
			case (SS_ALARM):
				LCD_SendStringXY(LCD_ALARM_L0, 0, 0);
			    LCD_SendStringXY(LCD_ALARM_L1, 1, 0);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN3, GPIO_LOW_PIN);
			    GPIO_voidWritePin(GPIO_B, GPIO_PIN1, GPIO_HIGH_PIN);
				break;				
			default:
				break;
			}//switch			
		}//if
		if(egBits & E_LCD_DISTANCE){
			switch(ParkingAssistance.SysState){
			case (SS_REVERSE):
				LCD_voidGotoXY(1, LCD_REV_DIGIT);
				LCD_voidDisplayInt(USONIC_u32Distance);
				break;
			case (SS_WARN):
				LCD_voidGotoXY(1, LCD_WARN_DIGIT);
                LCD_voidDisplayInt(USONIC_u32Distance);
				break;
			default:
				break;
			}//switch
		}//if
	}//while
}//T_Display
void T_Alarm(void* pvData){
	EventBits_t egBits = NULL;
	while(1){
		egBits = xEventGroupWaitBits(paEventGroup, (E_ALARM), 1, 0, portMAX_DELAY);
		if(egBits & (E_ALARM)){
			BUZZER_u8StartBuzzer();
			vTaskDelay(250);
			BUZZER_u8StopBuzzer();
		}//if		
	}//while
}//T_Alarm
void T_DistanceCheck(void* pvData){
	SystemState_t PrevState = SS_REVERSE;
	while(1){
		if((ParkingAssistance.SysState == SS_REVERSE) || (ParkingAssistance.SysState == SS_WARN) || (ParkingAssistance.SysState == SS_ALARM)){
			USONIC_voidTrigUSONIC(&PA_strUSONIC);
			if(USONIC_u32Distance <= 15){
				ParkingAssistance.SysState = SS_ALARM;
				xEventGroupSetBits(paEventGroup, (E_ALARM));
			}//if
			else if(USONIC_u32Distance <= 80){
				ParkingAssistance.SysState = SS_WARN;
				xEventGroupSetBits(paEventGroup, (E_LCD_DISTANCE));
			}//else if
			else{
				ParkingAssistance.SysState = SS_REVERSE;
				xEventGroupSetBits(paEventGroup, (E_LCD_DISTANCE));
			}//else		
		}//if
		if(ParkingAssistance.SysState != PrevState){
			PrevState = ParkingAssistance.SysState;
			xEventGroupSetBits(paEventGroup, (E_LCD_SCREEN));
		}//if
		vTaskDelay(20);
	}//while
}//T_DistanceCheck
/* Fns Definition */
void PA_voidInitSys(void){
EXTI_Config_t Loc_strRisingConfig  = {EXTI_0, EXTI_RISING	};
	EXTI_Config_t Loc_strForwardButton = {EXTI_1, EXTI_FALLING	};
	EXTI_Config_t Loc_strReverseButton = {EXTI_2, EXTI_FALLING	};
	
	TIM0_Config_t Loc_strUSONICTimer   = {	TIM0_NORMAL					,
											TIM0_OC0_NOT_CONNECTED		,
											TIM0_OC0_NOT_CONNECTED		,
											TIM0_OC0_NOT_CONNECTED		,
											TIM0_TOV_ENABLE				,
											TIM0_TOC_DISABLE			,
											TIM0_CLK_8					};
	TIM0_voidInit           (&Loc_strUSONICTimer                           );
	TIM0_voidStart          (&Loc_strUSONICTimer                           );
	EXTI_voidCBFSetter      (&Loc_strRisingConfig  ,USONIC_voidCalcDistance);
	EXTI_voidCBFSetter      (&Loc_strForwardButton ,PA_voidSetForwardState);
	EXTI_voidCBFSetter      (&Loc_strReverseButton ,PA_voidSetReverseState);
	EXTI_voidInit           (&Loc_strRisingConfig                          );
	EXTI_voidInit           (&Loc_strForwardButton                         );
	EXTI_voidInit           (&Loc_strReverseButton                         );
	USONIC_voidInit         (&PA_strUSONIC                                 );
	LCD_Init                (                                              );
	BUZZER_u8InitBuzzer     (                                              );
	GPIO_voidSetPinDirection(GPIO_B, GPIO_PIN1, GPIO_OUT_PIN               );
	GPIO_voidSetPinDirection(GPIO_B, GPIO_PIN3, GPIO_OUT_PIN               );
}//PA_voidInitSys
/* CallBack Fns */
void PA_voidSetReverseState(void){
	ParkingAssistance.SysState = SS_REVERSE;
}//PA_voidSetReverseState
void PA_voidSetForwardState(void){
	ParkingAssistance.SysState = SS_FORWARD;
}//PA_voidSetForwardState