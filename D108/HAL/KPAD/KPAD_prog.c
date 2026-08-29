/*
 * KPAD_prog.c
 *
 * Created: 8/29/2026 8:39:33 PM
 *  Author: adham
 */ 


#include "../../service/std_types.h"
#include "../../MCAL/DIO/dio.h"
#include "KPAD_config.h"
#include "KPAD_int.h"


static const u8 KPAD_COL_Arr[4] = {KPAD_COL_PIN0, KPAD_COL_PIN1, KPAD_COL_PIN2, KPAD_COL_PIN3};
static const u8 KPAD_ROW_Arr[4] = {KPAD_ROW_PIN0, KPAD_ROW_PIN1, KPAD_ROW_PIN2, KPAD_ROW_PIN3};
void KPAD_voidInit()
{
	for(u8 i=0;i<4;i++)
	{
		DIO_voidSetPinDir(KPAD_COL_PORT,KPAD_COL_Arr[i],DIO_PIN_OUTPUT);
		DIO_voidSetPinVal(KPAD_COL_PORT,KPAD_COL_Arr[i],DIO_PIN_HIGH);
		DIO_voidSetPinDir(KPAD_ROW_PORT,KPAD_COL_Arr[i],DIO_PIN_INPUT);
		DIO_voidEnablePullUp(KPAD_ROW_PORT,KPAD_COL_Arr[i]);
		
	}
}



u8 KPAD_u8GetKeyPressed()
{
	
}