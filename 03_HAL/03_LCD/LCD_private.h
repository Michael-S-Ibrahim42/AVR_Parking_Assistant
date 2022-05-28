/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :		   LCD
*/

/* The header file guard */
#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

	/* MACROS */
 	 #define GPIO_OUT_PORT        		0xFF

	/* Commands */
	#define CMD_CLEAR					0x01
	#define CMD_RET_HOME				0x02
	#define CMD_ENTRY_MODE				0x06
	#define CMD_DISP_ON					0x0C
	#define CMD_DISP_SHIFT_RIGHT		0x1C
	#define CMD_DISP_SHIFT_LEFT			0x18
	#define CMD_FN_SET					0x28
	#define CMD_SET_DDRAM_ADD			0x80

	/* Private Fns */
	static void LCD_EnablePort(void);
	
	

#endif
