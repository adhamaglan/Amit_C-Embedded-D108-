/*
 * KPAD_prog.c
 *
 * Created: 8/29/2026 8:39:33 PM
 *  Author: adham
 */ 
#define F_CPU 16000000ul

#include "../../service/std_types.h"
#include "../../service/bit_math.h"
#include "../../MCAL/DIO/dio.h"
#include "KPAD_priv.h"
#include "KPAD_config.h"
#include "KPAD_int.h"
#include <util/delay.h>


static const u8 KPAD_COL_Arr[KPAD_COL_NUM] = {KPAD_COL_PIN0, KPAD_COL_PIN1, KPAD_COL_PIN2, KPAD_COL_PIN3};
static const u8 KPAD_ROW_Arr[KPAD_ROW_NUM] = {KPAD_ROW_PIN0, KPAD_ROW_PIN1, KPAD_ROW_PIN2, KPAD_ROW_PIN3};
void KPAD_voidInit(void)
{
	for(u8 i=0;i<KPAD_ROW_COL_NUM;i++)
	{
		DIO_voidSetPinDir(KPAD_COL_PORT,KPAD_COL_Arr[i],DIO_PIN_OUTPUT);		// COL -> OUTPUT
		DIO_voidSetPinVal(KPAD_COL_PORT,KPAD_COL_Arr[i],DIO_PIN_HIGH);			// COL Value -> 1
		DIO_voidSetPinDir(KPAD_ROW_PORT,KPAD_ROW_Arr[i],DIO_PIN_INPUT);			// ROW -> INPUT (to be used as pull-up)
		DIO_voidEnablePullUp(KPAD_ROW_PORT,KPAD_ROW_Arr[i]);					// ROW -> Pull-Up
		
	}
}



u8 KPAD_u8GetKeyPressed(void)
{
	u8 Local_u8RowIdx;
	u8 Local_u8ColIdx;
	u8 Local_u8PinVal;
	u8 Local_u8PressedKey=KPAD_NO_PRESSED_KEY;
	
	static const u8 Local_u8KeyMatrix[KPAD_ROW_NUM][KPAD_COL_NUM]=KPAD_KEYS;
	
	// Looping through each COL
	for(Local_u8ColIdx=0;Local_u8ColIdx<KPAD_COL_NUM;Local_u8ColIdx++)
	{
		// Activate current COL by pulling it low
		DIO_voidSetPinVal(KPAD_COL_PORT,KPAD_COL_Arr[Local_u8ColIdx],DIO_PIN_LOW);
		// Read all ROW states for the active COL
		for(Local_u8RowIdx=0;Local_u8RowIdx<KPAD_ROW_NUM;Local_u8RowIdx++)
		{
			Local_u8PinVal=DIO_u8GetPinVal(KPAD_ROW_PORT,KPAD_ROW_Arr[Local_u8RowIdx]);
			// Check if ROW is pulled LOW (key pressed)
			if(Local_u8PinVal==0)
			{
				// Hardware De-bouncing: Wait for contact bounce to settle
				_delay_ms(20);
				// Re-verify pin state
				Local_u8PinVal=DIO_u8GetPinVal(KPAD_ROW_PORT,KPAD_ROW_Arr[Local_u8RowIdx]);
				if(Local_u8PinVal==0)
				{
					// Get the key position
					Local_u8PressedKey=Local_u8KeyMatrix[Local_u8RowIdx][Local_u8ColIdx];
					// Wait until button is released (by creating an infinite loop if button isn't released)
					while (DIO_u8GetPinVal(KPAD_ROW_PORT,KPAD_ROW_Arr[Local_u8RowIdx])==DIO_PIN_LOW);
					// Deactivate current COL before exiting
					DIO_voidSetPinVal(KPAD_COL_PORT,KPAD_COL_Arr[Local_u8ColIdx],DIO_PIN_HIGH);
					// return key
					return Local_u8PressedKey;
				}
			}
		}
		// Deactivate current COL before testing next COL
		DIO_voidSetPinVal(KPAD_COL_PORT,KPAD_COL_Arr[Local_u8ColIdx],DIO_PIN_HIGH);
	}
	return Local_u8PressedKey;
}