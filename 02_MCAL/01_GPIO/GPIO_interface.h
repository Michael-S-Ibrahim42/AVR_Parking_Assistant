/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :	       GPIO
*/

/* The header file guard */
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

    /* Ports */
    #define GPIO_A        0
    #define GPIO_B        1
    #define GPIO_C        2
    #define GPIO_D        3
    
    /* PINS */
    #define GPIO_PIN0            0
    #define GPIO_PIN1            1
    #define GPIO_PIN2            2
    #define GPIO_PIN3            3
    #define GPIO_PIN4            4
    #define GPIO_PIN5            5
    #define GPIO_PIN6            6
    #define GPIO_PIN7            7

	/* Select Port Direction */
    #define GPIO_OUT_PORT        0xFF
    #define GPIO_IN_PORT         0x00
    /* Pin Direction */
    #define GPIO_IN_PIN          0
	#define GPIO_OUT_PIN         1
    /* Port values */
    #define GPIO_HIGH_PORT       0xFF
    #define GPIO_LOW_PORT        0x00
    /* Pin Values */
    #define GPIO_LOW_PIN         0
	#define GPIO_HIGH_PIN        1

    /* Fn Prototypes */
    /* Setting Port Direction */
    void GPIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
    /* Setting Pin Direction */
    void GPIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
    /* Reading Port  */
    u8 GPIO_u8ReadPort(u8 Copy_u8Port);
    /* Reading Pin */
    u8 GPIO_u8ReadPin(u8 Copy_u8Port, u8 Copy_u8Pin);
    /* Writing Port */
    void GPIO_voidWritePort(u8 Copy_u8Port, u8 COPY_u8Value);
    /* Writing Pin */
    void GPIO_voidWritePin(u8 Copy_u8Port, u8 Copy_u8Pin, u8 COPY_u8Value);
    /* Toggle pin output value */
    void GPIO_voidTogPinVal(u8 Copy_u8Port, u8 Copy_u8Pin);
	/* Setting Port Mask Direction */
	void GPIO_voidSetPortMaskDirection(u8 Copy_u8Port, u8 Copy_u8Mask, u8 Copy_u8Direction);
	/* Setting Port Mask Value */
	void GPIO_voidSetPortMaskValue(u8 Copy_u8Port, u8 Copy_u8Mask, u8 Copy_u8Value);
#endif
