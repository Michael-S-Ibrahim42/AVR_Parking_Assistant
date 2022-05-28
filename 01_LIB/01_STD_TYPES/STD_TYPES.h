/* 
* Name         :           Michael S. Ibrahim
* Date         :           September 14, 2021
* Version      :           V01
* SWC		   :     	   STD_TYPES
*/

/* The header file guard */
#ifndef STD_TYPES_H
#define STD_TYPES_H
    /* MACROS */
	#define NULL							(void*)0
    /* The needed data types */
    typedef unsigned char           		u8;
    typedef signed char             		s8;
    typedef unsigned short int      		u16;
    typedef signed short int        		s16;
    typedef unsigned long int       		u32;
    typedef signed long int         		s32;
	typedef unsigned long long int  		u64;
	typedef signed long long int			s64;	
    typedef float                   		f32;
    typedef double                  		f64;
    typedef long double             		f80;
	typedef enum{
		FALSE = 0,
		TRUE
	}bool_t;
	
#endif
