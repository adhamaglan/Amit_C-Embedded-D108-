/*
 * CLCD_int.h
 *
 * Created: 8/28/2026 7:11:36 PM
 *  Author: adham
 */ 


#ifndef CLCD_INT_H_
#define CLCD_INT_H_



void CLCD_voidInit(void);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendInst(u8 Copy_u8Data);
void CLCD_voidSendString(const u8 *Copy_u8Str);
void CLCD_voidSstCursorPos(u8 x,u8 y);
void CLCD_voidClearScreen(void);
void CLCD_voidSendSpecialChar(u8 Copy_u8Index,const u8 *Copy_u8Arr,u8 Copyu8x,u8 Copyu8y);



#endif /* CLCD_INT_H_ */