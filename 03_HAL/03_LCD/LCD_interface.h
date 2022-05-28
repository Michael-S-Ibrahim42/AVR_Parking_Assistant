/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   LCD
*/

/* The header file guard */
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H
	/* MACROS */
	#define LCD_ROW0					0x00
	#define LCD_ROW1					0x40
	#define LCD_COL0					0
	#define LCD_COL1					1
	#define LCD_COL2					2
	#define LCD_COL3					3
	#define LCD_COL4					4
	#define LCD_COL5					5
	#define LCD_COL6					6
	#define LCD_COL7					7
	#define LCD_COL8					8
	#define LCD_COL9					9
	#define LCD_COL10					10
	#define LCD_COL11					11
	#define LCD_COL12					12
	#define LCD_COL13					13
	#define LCD_COL14					14
	#define LCD_COL15					15
	/* Fns Prototypes */
	void LCD_Init(void);
	void LCD_SendData(u8 Copy_u8Data);
	void LCD_SendCMD(u8 Copy_u8CMD);
	void LCD_SendString(u8 *Copy_u8Data);
	void LCD_SendStringXY(u8 *Copy_u8Data, u8 Copy_u8Row, u8 Copy_u8Col);
	void LCD_DispWelcomeScreen(void);
	void LCD_voidDisplayInt(u32 Copy_u32Integer);
	void LCD_voidGotoXY(u8 Copy_u8Row, u8 Copy_u8Col);
#endif
