/*
 * D108.c
 *
 * Created: 8/15/2026 6:57:42 PM
 * Author : adham
 */ 
#define F_CPU 16000000ul


#include "service/std_types.h"
#include "service/bit_math.h"
#include "MCAL/regdef.h"
#include "MCAL/DIO/dio.h"
#include "HAL/CLCD/CLCD_config.h"
#include "HAL/CLCD/CLCD_int.h"
#include "HAL/KPAD/KPAD_config.h"
#include "HAL/KPAD/KPAD_int.h"
#include <util/delay.h>

int main(void)
{
	u8 Local_u8PressedKey=KPAD_NO_PRESSED_KEY;

	CLCD_voidInit();
	KPAD_voidInit();

    while (1) 
    {
		Local_u8PressedKey=KPAD_u8GetKeyPressed();
		if (Local_u8PressedKey != KPAD_NO_PRESSED_KEY)
		{

			if (Local_u8PressedKey=='c')
			{
				CLCD_voidClearScreen();
			}
			else
			{
				CLCD_voidSendData(Local_u8PressedKey);
			}
		}
	}
}
