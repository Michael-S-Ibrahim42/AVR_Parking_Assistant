/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :           GPIO
*/

/* LIB Layer */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "ATMEGA32A.h"
/* Module headers */
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/* Setting Port Direction */
void GPIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction){
    switch(Copy_u8Port){
        case(GPIO_A):
            GPIO_DDRA = Copy_u8Direction;
            break;      
        case(GPIO_B):   
            GPIO_DDRB = Copy_u8Direction;
            break;      
        case(GPIO_C):   
            GPIO_DDRC = Copy_u8Direction;
            break;       
        case(GPIO_D):    
            GPIO_DDRD = Copy_u8Direction;
            break;
		default:break;
    }
}//GPIO_voidSetPortDirection
/* Setting Port Mask Direction */
void GPIO_voidSetPortMaskDirection(u8 Copy_u8Port, u8 Copy_u8Mask, u8 Copy_u8Direction){
	switch(Copy_u8Port){
	case (GPIO_A):
		if(Copy_u8Direction){
			GPIO_DDRA |= (Copy_u8Mask & Copy_u8Direction);
		}//if
		else{
			GPIO_DDRA &= ~(Copy_u8Mask);
		}//else
		break;
	case (GPIO_B):
		if(Copy_u8Direction){
			GPIO_DDRA |= (Copy_u8Mask & Copy_u8Direction);
		}//if
		else{
			GPIO_DDRA &= ~(Copy_u8Mask);
		}//else
		break;
	case (GPIO_C):
		if(Copy_u8Direction){
			GPIO_DDRA |= (Copy_u8Mask & Copy_u8Direction);
		}//if
		else{
			GPIO_DDRA &= ~(Copy_u8Mask);
		}//else
		break;
	case (GPIO_D):
		if(Copy_u8Direction){
			GPIO_DDRA |= (Copy_u8Mask & Copy_u8Direction);
		}//if
		else{
			GPIO_DDRA &= ~(Copy_u8Mask);
		}//else
		break;
	}//switc
}//GPIO_voidSetPortMaskDirection
/* Setting Port Mask Value */
void GPIO_voidSetPortMaskValue(u8 Copy_u8Port, u8 Copy_u8Mask, u8 Copy_u8Value){
	switch(Copy_u8Port){
	case (GPIO_A):
		if(Copy_u8Value != 0){
			GPIO_PORTA &= ~(Copy_u8Mask);
			GPIO_PORTA |= (Copy_u8Mask & Copy_u8Value);
		}
		else{
			GPIO_PORTA &= ~(Copy_u8Mask);
		}
		break;
	case (GPIO_B):
		if(Copy_u8Value){
			GPIO_PORTB &= ~(Copy_u8Mask);
			GPIO_PORTB |= (Copy_u8Mask & Copy_u8Value);
		}
		else{
			GPIO_PORTB &= ~(Copy_u8Mask);
		}
		break;
	case (GPIO_C):
		if(Copy_u8Value){
			GPIO_PORTC &= ~(Copy_u8Mask);
			GPIO_PORTC |= (Copy_u8Mask & Copy_u8Value);
		}
		else{
			GPIO_PORTC &= ~(Copy_u8Mask);
		}
		break;
	case (GPIO_D):
		if(Copy_u8Value){
			GPIO_PORTD &= ~(Copy_u8Mask);
			GPIO_PORTD |= (Copy_u8Mask & Copy_u8Value);
		}
		else{
			GPIO_PORTD &= ~(Copy_u8Mask);
		}
		break;
	}//switch
}//GPIO_voidSetPortMaskValue
/* Setting Pin Direction */
void GPIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction){
    switch(Copy_u8Port){
        case(GPIO_A):
            if(Copy_u8Direction == GPIO_OUT_PIN){
            	SET_BIT(GPIO_DDRA, Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_IN_PIN){
                CLR_BIT(GPIO_DDRA, Copy_u8Pin);
            }
            break;
        case(GPIO_B):
            if(Copy_u8Direction == GPIO_OUT_PIN){
                SET_BIT(GPIO_DDRB, Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_IN_PIN){
                CLR_BIT(GPIO_DDRB, Copy_u8Pin);
            }
            break;
        case(GPIO_C):
            if(Copy_u8Direction == GPIO_OUT_PIN){
                SET_BIT(GPIO_DDRC, Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_IN_PIN){
                CLR_BIT(GPIO_DDRC, Copy_u8Pin);
            }
            break;        
        case(GPIO_D):
            if(Copy_u8Direction == GPIO_OUT_PIN){
                SET_BIT(GPIO_DDRD, Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_IN_PIN){
                CLR_BIT(GPIO_DDRD, Copy_u8Pin);
            }
            break;  
		default:break;
    }
}//GPIO_voidSetPinDirection
/* Reading Port  */
u8 GPIO_u8ReadPort(u8 Copy_u8Port){
    u8 Loc_u8Value = 0;
    switch(Copy_u8Port){
        case(GPIO_A):
            Loc_u8Value = GPIO_PINA;
            break;
        case(GPIO_B):
            Loc_u8Value = GPIO_PINB;
            break;
        case(GPIO_C):
            Loc_u8Value = GPIO_PINC;
            break;
        case(GPIO_D):
            Loc_u8Value = GPIO_PIND;
            break;
		default:break;
    }
    return(Loc_u8Value);
}//GPIO_u8ReadPort
/* Reading Pin */
u8 GPIO_u8ReadPin(u8 Copy_u8Port, u8 Copy_u8Pin){
    u8 Loc_u8Value = 0;
    switch(Copy_u8Port){
        case(GPIO_A):
            Loc_u8Value = GET_BIT(GPIO_PINA, Copy_u8Pin);
            break;
        case(GPIO_B):
            Loc_u8Value = GET_BIT(GPIO_PINB, Copy_u8Pin);
            break;
        case(GPIO_C):
            Loc_u8Value = GET_BIT(GPIO_PINC, Copy_u8Pin);
            break;
        case(GPIO_D):
            Loc_u8Value = GET_BIT(GPIO_PIND, Copy_u8Pin);
            break;
		default:break;
    }
    return(Loc_u8Value);
}//GPIO_u8ReadPin
/* Writing Port */
void GPIO_voidWritePort(u8 Copy_u8Port, u8 Copy_u8Value){
    switch(Copy_u8Port){
        case(GPIO_A):
            GPIO_PORTA = Copy_u8Value;
            break;
        case(GPIO_B):
            GPIO_PORTB = Copy_u8Value;
            break;
        case(GPIO_C):
            GPIO_PORTC = Copy_u8Value;
            break;
        case(GPIO_D):
            GPIO_PORTD = Copy_u8Value;
            break;
		default:break;
    }
}
/* Writing Pin */
void GPIO_voidWritePin(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value){
    switch(Copy_u8Port){
        case(GPIO_A):
            if(Copy_u8Value == GPIO_HIGH_PIN){
                SET_BIT(GPIO_PORTA, Copy_u8Pin);
            }
            else if(Copy_u8Value == GPIO_LOW_PIN){
                CLR_BIT(GPIO_PORTA, Copy_u8Pin);
            }
            break;
        case(GPIO_B):
            if(Copy_u8Value == GPIO_HIGH_PIN){
                SET_BIT(GPIO_PORTB, Copy_u8Pin);
            }
            else if(Copy_u8Value == GPIO_LOW_PIN){
                CLR_BIT(GPIO_PORTB, Copy_u8Pin);
            }
            break;
        case(GPIO_C):
            if(Copy_u8Value == GPIO_HIGH_PIN){
                SET_BIT(GPIO_PORTC, Copy_u8Pin);
            }
            else if(Copy_u8Value == GPIO_LOW_PIN){
                CLR_BIT(GPIO_PORTC, Copy_u8Pin);
            }
            break;
        case(GPIO_D):
            if(Copy_u8Value == GPIO_HIGH_PIN){
                SET_BIT(GPIO_PORTD, Copy_u8Pin);
            }
            else if(Copy_u8Value == GPIO_LOW_PIN){
                CLR_BIT(GPIO_PORTD, Copy_u8Pin);
            }
            break;
		default:break;
    }
}//GPIO_voidTogVal
/* Fn to toggle the pin output value */
void GPIO_voidTogPinVal(u8 Copy_u8Port, u8 Copy_u8Pin){
    switch(Copy_u8Port){
	case GPIO_A:
		TOG_BIT(GPIO_PORTA, Copy_u8Pin);
		break;
	case GPIO_B:
		TOG_BIT(GPIO_PORTB, Copy_u8Pin);
		break;
	case GPIO_C:
		TOG_BIT(GPIO_PORTC, Copy_u8Pin);
		break;
	case GPIO_D:
		TOG_BIT(GPIO_PORTD, Copy_u8Pin);
		break;
	default:break;
    }
}//GPIO_voidTogVal
