/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   LCD
*/
#define F_CPU       16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_Init(void){
	GPIO_voidSetPortDirection(LCD_PORT, GPIO_OUT_PORT);
	_delay_ms(100);
	LCD_SendCMD(CMD_FN_SET>>4);
	LCD_SendCMD(CMD_FN_SET);
	LCD_SendCMD(CMD_DISP_ON);
	LCD_SendCMD(CMD_ENTRY_MODE);
	LCD_SendCMD(CMD_CLEAR);
	_delay_ms(5);
}
void LCD_SendData(u8 Copy_u8Data){
	GPIO_voidWritePin(LCD_PORT, LCD_RS_PIN, 1);
	GPIO_voidSetPortMaskValue(LCD_PORT, LCD_DATA_MASK, Copy_u8Data);
	LCD_EnablePort();
	GPIO_voidSetPortMaskValue(LCD_PORT, LCD_DATA_MASK, Copy_u8Data<<4);
	LCD_EnablePort();
	_delay_us(40);
}
void LCD_SendString(u8 *Copy_u8Data){
	while(*Copy_u8Data){
		LCD_SendData(*Copy_u8Data);
		Copy_u8Data++;
	}//while
}//LCD_SendString
void LCD_voidGotoXY(u8 Copy_u8Row, u8 Copy_u8Col){
	if(Copy_u8Row == LCD_ROW0){
		LCD_SendCMD((CMD_SET_DDRAM_ADD|LCD_ROW0) + (Copy_u8Col));
	}//if
	else{
		LCD_SendCMD((CMD_SET_DDRAM_ADD|LCD_ROW1) + (Copy_u8Col));
	}//else
}//LCD_voidGotoXY
void LCD_voidDisplayInt(u32 Copy_u32Integer){
	u32 Loc_u32ReversedNumber = 0;
	u8 Loc_u8Digit;
	u64 i = 1;
	while(Copy_u32Integer){
		Loc_u32ReversedNumber = Copy_u32Integer % 10 + (Loc_u32ReversedNumber * 10);
		Copy_u32Integer /= 10;
		i *= 10;
	}//while
	while(i != 1){
		Loc_u8Digit = (Loc_u32ReversedNumber%10) + '0';
		LCD_SendData(Loc_u8Digit);
		Loc_u32ReversedNumber /= 10;
		i /= 10;
	}//while
}//LCD_voidDisplayInt
void LCD_SendCMD(u8 Copy_u8CMD){
	GPIO_voidWritePin(LCD_PORT, LCD_RS_PIN, 0);
	GPIO_voidSetPortMaskValue(LCD_PORT, LCD_DATA_MASK, Copy_u8CMD);
	LCD_EnablePort();
	GPIO_voidSetPortMaskValue(LCD_PORT, LCD_DATA_MASK, Copy_u8CMD<<4);
	LCD_EnablePort();
	_delay_us(40);
}
static void LCD_EnablePort(void){
	GPIO_voidWritePin(LCD_PORT, LCD_EN_PIN, 1);
	GPIO_voidWritePin(LCD_PORT, LCD_EN_PIN, 0);
}
void LCD_SendStringXY(u8 *Copy_u8Data, u8 Copy_u8Row, u8 Copy_u8Col){
	if(Copy_u8Row == LCD_ROW0){
		LCD_SendCMD((CMD_SET_DDRAM_ADD|LCD_ROW0) + (Copy_u8Col));
		LCD_SendString(Copy_u8Data);
	}//if
	else{
		LCD_SendCMD((CMD_SET_DDRAM_ADD|LCD_ROW1) + (Copy_u8Col));
		LCD_SendString(Copy_u8Data);
	}//else
}
void LCD_DispWelcomeScreen(void){
	u8 Loc_u8MovesNumber = 3, Loc_u8Iterator;
	LCD_SendStringXY("Welcome", LCD_ROW0, LCD_COL4);
	while(Loc_u8MovesNumber--){
		for(Loc_u8Iterator = 0; Loc_u8Iterator < 4; Loc_u8Iterator++){
			LCD_SendCMD(CMD_DISP_SHIFT_LEFT);
			_delay_ms(500);
		}
		for(Loc_u8Iterator = 0; Loc_u8Iterator < 9; Loc_u8Iterator++){
			LCD_SendCMD(CMD_DISP_SHIFT_RIGHT);
			_delay_ms(500);
		}
		for(Loc_u8Iterator = 0; Loc_u8Iterator < 5; Loc_u8Iterator++){
			LCD_SendCMD(CMD_DISP_SHIFT_LEFT);
			_delay_ms(500);
		}
	}
}
