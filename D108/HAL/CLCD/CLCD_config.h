/*
 * CLCD_config.h
 *
 * Created: 8/28/2026 7:11:18 PM
 *  Author: adham
 */ 


#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_



#define CLCD_TYPE			CLCD_4_BITS		//  choose interface between (CLCD_4_BITS or CLCD_8_BITS)
#define CLCD_DATA_PORT		DIO_PORTA		//  choose Data Port

#if CLCD_TYPE == CLCD_4_BITS
#define  CLCD_DATA_PIN0		DIO_PIN4		//  choose Data Pin0
#define  CLCD_DATA_PIN1		DIO_PIN5		//	choose Data Pin1
#define  CLCD_DATA_PIN2		DIO_PIN6		//	choose Data Pin2
#define  CLCD_DATA_PIN3		DIO_PIN7		//	choose Data Pin3
#endif

#define CLCD_CTRL_PORT		DIO_PORTB		//	choose Ctrl Port

#define CLCD_RS_PIN		DIO_PIN1			//	choose Ctrl RS Pin
#define CLCD_RW_PIN		DIO_PIN0			//	choose Ctrl RW Pin
#define CLCD_E_PIN		DIO_PIN2			//	choose Ctrl E  Pin



#endif /* CLCD_CONFIG_H_ */