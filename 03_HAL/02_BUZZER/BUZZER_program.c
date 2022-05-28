/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   BUZZER
*/

/* Including Libraries */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_interface.h"
/* Own  SWC files */
#include "BUZZER_interface.h"
#include "BUZZER_private.h"
#include "BUZZER_config.h"

/* Fns Definitions */
u8 BUZZER_u8InitBuzzer(void){
	GPIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, GPIO_OUT_PIN);
	return(0);
}//BUZZER_u8InitBuzzer
u8 BUZZER_u8StartBuzzer(void){
	GPIO_voidWritePin(BUZZER_PORT, BUZZER_PIN, GPIO_HIGH_PIN);
	return(0);
}//BUZZER_u8StartBuzzer
u8 BUZZER_u8StopBuzzer(void){
	GPIO_voidWritePin(BUZZER_PORT, BUZZER_PIN, GPIO_LOW_PIN);
	return(0);
}//BUZZER_u8StopBuzzer
