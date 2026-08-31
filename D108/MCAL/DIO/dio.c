/*
 * dio.c
 *
 * Created: 8/15/2026 8:34:18 PM
 *  Author: adham
 */ 

#include "../../service/std_types.h"
#include "../../service/bit_math.h"
#include "../regdef.h"
#include "dio.h"


void DIO_voidSetPinDir (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Dir)
{
	if ((Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7))
	{
		if (Copy_u8Dir == DIO_PIN_OUTPUT)
		{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA: SET_BIT(DDRA_REG, Copy_u8PinID); break;
				case DIO_PORTB: SET_BIT(DDRB_REG, Copy_u8PinID); break;
				case DIO_PORTC: SET_BIT(DDRC_REG, Copy_u8PinID); break;
				case DIO_PORTD: SET_BIT(DDRD_REG, Copy_u8PinID); break;
				default: break; // error Invalid PortID
			}
		}
		else if (Copy_u8Dir == DIO_PIN_INPUT)
		{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA: CLR_BIT(DDRA_REG, Copy_u8PinID); break;
				case DIO_PORTB: CLR_BIT(DDRB_REG, Copy_u8PinID); break;
				case DIO_PORTC: CLR_BIT(DDRC_REG, Copy_u8PinID); break;
				case DIO_PORTD: CLR_BIT(DDRD_REG, Copy_u8PinID); break;
				default: break; // error Invalid PortID
			}
		}
		else
		{
			// error Invalid Direction (INP/OUT)
		}
	}
	else
	{
		// error Invalid Port or Pin ID
	}
}


void DIO_voidSetPinVal (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Val)
{
	if ((Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7))
	{
		if (Copy_u8Val == DIO_PIN_HIGH)
		{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA: SET_BIT(PORTA_REG, Copy_u8PinID); break;
				case DIO_PORTB: SET_BIT(PORTB_REG, Copy_u8PinID); break;
				case DIO_PORTC: SET_BIT(PORTC_REG, Copy_u8PinID); break;
				case DIO_PORTD: SET_BIT(PORTD_REG, Copy_u8PinID); break;
				default: break; // error Invalid PortID
			}
		}
		else if (Copy_u8Val == DIO_PIN_LOW)
		{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA: CLR_BIT(PORTA_REG, Copy_u8PinID); break;
				case DIO_PORTB: CLR_BIT(PORTB_REG, Copy_u8PinID); break;
				case DIO_PORTC: CLR_BIT(PORTC_REG, Copy_u8PinID); break;
				case DIO_PORTD: CLR_BIT(PORTD_REG, Copy_u8PinID); break;
				default: break; // error Invalid PortID
			}
		}
		else
		{
			// error Invalid Value (HIGH/LOW)
		}
	}
	else
	{
		// error Invalid Port or Pin ID
	}
}


u8 DIO_u8GetPinVal (u8 Copy_u8PortID, u8 Copy_u8PinID)
{
	u8 Local_u8PinVal = DIO_PIN_LOW;

	if ((Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7))
	{
		switch (Copy_u8PortID)
		{
			case DIO_PORTA: Local_u8PinVal = GET_BIT(PINA_REG, Copy_u8PinID); break;
			case DIO_PORTB: Local_u8PinVal = GET_BIT(PINB_REG, Copy_u8PinID); break;
			case DIO_PORTC: Local_u8PinVal = GET_BIT(PINC_REG, Copy_u8PinID); break;
			case DIO_PORTD: Local_u8PinVal = GET_BIT(PIND_REG, Copy_u8PinID); break;
			default: break; // error Invalid PortID
		}
	}
	else
	{
		// error Invalid Port or Pin ID
	}
	return Local_u8PinVal;
}


void DIO_voidSetPortDir (u8 Copy_u8PortID, u8 Copy_u8Dir)
{
	if (Copy_u8PortID <= DIO_PORTD)
	{
			switch (Copy_u8PortID)
			{
				case DIO_PORTA: DDRA_REG=Copy_u8Dir; break;
				case DIO_PORTB: DDRB_REG=Copy_u8Dir; break;
				case DIO_PORTC: DDRC_REG=Copy_u8Dir; break;
				case DIO_PORTD: DDRD_REG=Copy_u8Dir; break;
				default: break; // error Invalid PortID
			}
	}
	else
	{
		//error Invalid PortID
	}
}


void DIO_voidSetPortVal (u8 Copy_u8PortID, u8 Copy_u8Val)
{
	if (Copy_u8PortID <= DIO_PORTD)
	{
		switch (Copy_u8PortID)
		{
			case DIO_PORTA: PORTA_REG = Copy_u8Val; break;
			case DIO_PORTB: PORTB_REG = Copy_u8Val; break;
			case DIO_PORTC: PORTC_REG = Copy_u8Val; break;
			case DIO_PORTD: PORTD_REG = Copy_u8Val; break;
			default: break; // error Invalid PortID
		}
	}
	else
	{
		//error Invalid PortID
	}
}


u8	 DIO_u8GetPortVal (u8 Copy_u8PortID)
{
	u8 Local_u8PortVal = DIO_PORT_LOW;
	if (Copy_u8PortID <= DIO_PORTD)
	{
		switch (Copy_u8PortID)
		{
			case DIO_PORTA: Local_u8PortVal = PINA_REG; break;
			case DIO_PORTB: Local_u8PortVal = PINB_REG; break;
			case DIO_PORTC: Local_u8PortVal = PINC_REG; break;
			case DIO_PORTD: Local_u8PortVal = PIND_REG; break;
			default: break; // error Invalid PortID
		}
	}
	else
	{
		// error Invalid PortID
	}
	return Local_u8PortVal;
}


void DIO_voidTogPinVal  (u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	if ((Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7))
	{
		switch (Copy_u8PortID)
		{
			case DIO_PORTA: TOG_BIT(PORTA_REG, Copy_u8PinID); break;
			case DIO_PORTB: TOG_BIT(PORTB_REG, Copy_u8PinID); break;
			case DIO_PORTC: TOG_BIT(PORTC_REG, Copy_u8PinID); break;
			case DIO_PORTD: TOG_BIT(PORTD_REG, Copy_u8PinID); break;
			default: break; // error Invalid PortID
		}
	}
	else
	{
		// error Invalid Port or Pin ID
	}
}


void DIO_voidEnablePullUp (u8 Copy_u8PortID,u8 Copy_u8PinID)	// Pin direction must be set to INPUT first
{
	if ((Copy_u8PortID <= DIO_PORTD) && (Copy_u8PinID <= DIO_PIN7))
	{
		switch (Copy_u8PortID)
		{
			case DIO_PORTA: if(GET_BIT(DDRA_REG,Copy_u8PinID)==0)
							{ 
								SET_BIT(PORTA_REG, Copy_u8PinID);
							}
							else
							{
								// error Pin not initialized as Input
							}break;
			case DIO_PORTB: if(GET_BIT(DDRB_REG,Copy_u8PinID)==0)
							{ 
								SET_BIT(PORTB_REG, Copy_u8PinID);
							}
							else
							{
								// error Pin not initialized as Input
							}break;
			case DIO_PORTC: if(GET_BIT(DDRC_REG,Copy_u8PinID)==0)
							{ 
								SET_BIT(PORTC_REG, Copy_u8PinID);
							}
							else
							{
								// error Pin not initialized as Input
							}break;
			case DIO_PORTD: if(GET_BIT(DDRD_REG,Copy_u8PinID)==0)
							{ 
								SET_BIT(PORTD_REG, Copy_u8PinID);
							}
							else
							{
								// error Pin not initialized as Input
							}break;
			default: break; // error Invalid PortID
		}
	}
	else
	{
		// error Invalid Port or Pin ID
	}
}
