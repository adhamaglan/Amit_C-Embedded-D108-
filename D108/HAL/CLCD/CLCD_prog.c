/*
 * CLCD_prog.c
 *
 * Created: 8/28/2026 7:12:01 PM
 *  Author: adham
 */ 
#define F_CPU 16000000ul

#include "../../service/std_types.h"
#include "../../service/bit_math.h"
#include "../../MCAL/DIO/dio.h"
#include "CLCD_priv.h"
#include "CLCD_config.h"
#include "CLCD_int.h"
#include <util/delay.h>



void static sendEnablePulse(void)
{
	DIO_voidSetPinVal (CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(10);
	DIO_voidSetPinVal (CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_LOW);
}



#if CLCD_TYPE == CLCD_4_BITS
static void setHalfPort(u8 data)
{
		DIO_voidSetPinVal(CLCD_DATA_PORT,CLCD_DATA_PIN0, GET_BIT(data, 0));
		DIO_voidSetPinVal(CLCD_DATA_PORT,CLCD_DATA_PIN1, GET_BIT(data, 1));
		DIO_voidSetPinVal(CLCD_DATA_PORT,CLCD_DATA_PIN2, GET_BIT(data, 2));
		DIO_voidSetPinVal(CLCD_DATA_PORT,CLCD_DATA_PIN3, GET_BIT(data, 3));
}
#endif



void CLCD_voidInit(void)
{
		DIO_voidSetPinDir(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_PIN_OUTPUT);
		DIO_voidSetPinDir(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_PIN_OUTPUT);
		DIO_voidSetPinDir(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_OUTPUT);
		#if CLCD_TYPE == CLCD_8_BITS
		DIO_voidSetPortDir(CLCD_DATA_PORT,DIO_PORT_OUTPUT);
		#elif CLCD_TYPE == CLCD_4_BITS
		DIO_voidSetPinDir(CLCD_DATA_PORT,CLCD_DATA_PIN0,DIO_PIN_OUTPUT);
		DIO_voidSetPinDir(CLCD_DATA_PORT,CLCD_DATA_PIN1,DIO_PIN_OUTPUT);
		DIO_voidSetPinDir(CLCD_DATA_PORT,CLCD_DATA_PIN2,DIO_PIN_OUTPUT);
		DIO_voidSetPinDir(CLCD_DATA_PORT,CLCD_DATA_PIN3,DIO_PIN_OUTPUT);
		#else
		#warning "Wrong CLCD Type Choice"
		#endif
		_delay_ms(40);
		#if CLCD_TYPE == CLCD_8_BITS
		// Function Set: 8-bit mode, 2 lines display, 5x7 font matrix 
		CLCD_voidSendInst(0x38);
		#elif CLCD_TYPE == CLCD_4_BITS
		// Function Set: 4-bit mode, 2 lines display, 5x7 font matrix 
		setHalfPort(0x02);
		sendEnablePulse();
		setHalfPort(0x02);
		sendEnablePulse();
		setHalfPort(0x08);
		sendEnablePulse();
		#endif
		// Display ON/OFF: Display ON, Cursor ON, Blink ON 
		CLCD_voidSendInst(0x0F);
		// Clear Display 
		CLCD_voidSendInst(0x01);
}



void CLCD_voidSendData(u8 Copy_u8Data)
{
	// Data mode
	DIO_voidSetPinVal(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinVal(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	#if CLCD_TYPE == CLCD_8_BITS
	// send data
	DIO_voidSetPortVal (CLCD_DATA_PORT,Copy_u8Data);
	// pulse
	sendEnablePulse();
	#elif CLCD_TYPE == CLCD_4_BITS
	// send High nibble data
	setHalfPort(Copy_u8Data >> 4); 
	// pulse
	sendEnablePulse();
	// send Low nibble data
	setHalfPort(Copy_u8Data & 0x0f);
	// pulse
	sendEnablePulse();
	#else
	#warning "Wrong CLCD Type Choice"
	#endif	
}



void CLCD_voidSendInst(u8 Copy_u8Data)
{
	// Instruction mode
	DIO_voidSetPinVal(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_LOW);
	DIO_voidSetPinVal(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	#if CLCD_TYPE == CLCD_8_BITS
	// send instruction
	DIO_voidSetPortVal (CLCD_DATA_PORT,Copy_u8Data);
	// pulse
	sendEnablePulse();
	#elif CLCD_TYPE == CLCD_4_BITS
	// send High nibble instruction
	setHalfPort(Copy_u8Data >> 4);
	// pulse
	sendEnablePulse();
	// send Low nibble instruction
	setHalfPort(Copy_u8Data & 0x0f);
	// pulse
	sendEnablePulse();
	#else
	#warning "Wrong CLCD Type Choice"
	#endif
}



void CLCD_voidSendString(const u8 *Copy_u8Str)
{
	u8 Local_u8Index = 0;
	while (Copy_u8Str[Local_u8Index] != '\0')
	{
		// adding new line command '\n'
		if (Copy_u8Str[Local_u8Index]=='\n')
		{
			CLCD_voidSetCursorPos(0,1);
		}else
		{
			CLCD_voidSendData(Copy_u8Str[Local_u8Index]);
		}
		Local_u8Index++;
	}
}



void CLCD_voidSendNumber(s32 Copy_s32Number)
{
	u8 Local_u8Buffer[10];
	//  A 32-bit signed integer has a maximum value of 2,147,483,647 (10 digits)
	s8 Local_s8Idx = 0;
	//	track the number of digits added to Local_u8Buffer
	u32 Local_u32Num;
	if (Copy_s32Number==0)
	{
		CLCD_voidSendData('0');
		return;
	}
	if (Copy_s32Number<0)
	{
		CLCD_voidSendData('-');
		//	printing the -ve sign
		Local_u32Num= -(u32)Copy_s32Number;
		//	Cast to u32 before negation to safely handle the 32bit int limit
		//	(-2,147,483,648) -> (2,147,483,648) !!overflow +ve 32bit int limit is (2,147,483,647)
		
	}
	else
	{
		Local_u32Num=(u32)Copy_s32Number;
	}
	while(Local_u32Num>0)
	{
		Local_u8Buffer[Local_s8Idx++]=(Local_u32Num%10)+'0';
		//	stores the rightmost digit in the buffer array
		//  (Local_u32Num%10)+'0' -> adds the ASCII offset of char '0' to obtain the digit's ASCII
		Local_u32Num/=10;
		//	integer division equivalent to removing (dropping) the rightmost digit
	}
	while (Local_s8Idx > 0)
	{
		CLCD_voidSendData(Local_u8Buffer[--Local_s8Idx]);
		//	sends the number in the form of an array containing each digit's ASCII 
		//  to print as char on CLCD
	}
}



void CLCD_voidSetCursorPos(u8 Copy_u8x,u8 Copy_u8y)
{
	u8 address=Copy_u8x+Copy_u8y*0x40;
	SET_BIT(address,7);
	CLCD_voidSendInst(address);
}



void CLCD_voidClearScreen(void)
{
	CLCD_voidSendInst(0x01);
	_delay_ms(10);
}



void CLCD_voidSendSpecialChar(u8 Copy_u8Index,const u8 *Copy_u8Arr,u8 Copy_u8x,u8 Copy_u8y)
{
	u8 address=Copy_u8Index * 8;
	SET_BIT(address,6);
	CLCD_voidSendInst(address);
	for(u8 i=0;i<8;i++)
	{
		CLCD_voidSendData(Copy_u8Arr[i]);
	}
	// char stored in CGRAM
	CLCD_voidSetCursorPos(Copy_u8x,Copy_u8y);
	CLCD_voidSendData(Copy_u8Index);
}