/*
 * dio.h
 *
 * Created: 8/15/2026 8:34:07 PM
 *  Author: adham
 */ 

#ifndef DIO_H_
#define DIO_H_

#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7

#define DIO_PIN_INPUT    0
#define DIO_PIN_OUTPUT   1
#define DIO_PORT_INPUT   0x00
#define DIO_PORT_OUTPUT  0xff

#define DIO_PIN_LOW    0
#define DIO_PIN_HIGH   1
#define DIO_PORT_LOW   0x00
#define DIO_PORT_HIGH  0xff

void DIO_voidSetPinDir (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Dir);
void DIO_voidSetPinVal (u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8Val);
u8	 DIO_u8GetPinVal   (u8 Copy_u8PortID, u8 Copy_u8PinID);

void DIO_voidSetPortDir (u8 Copy_u8PortID, u8 Copy_u8Dir);
void DIO_voidSetPortVal (u8 Copy_u8PortID, u8 Copy_u8Val);
u8	 DIO_u8GetPortVal   (u8 Copy_u8PortID);

void DIO_viodTogPinVal  (u8 Copy_u8PortID,u8 Copy_u8PinID);

void DIO_voidEnablePullUp (u8 Copy_u8PortID,u8 Copy_u8PinID);



#endif /* DIO_H_ */