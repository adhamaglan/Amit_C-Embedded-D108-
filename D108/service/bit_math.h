/*
 * bit_math.h 
 *
 * Created: 8/15/2026 8:03:46 PM
 *  Author: adham
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,bit) ((reg)|=(1<<(bit)))
#define CLR_BIT(reg,bit) ((reg)&=~(1<<(bit)))
#define TOG_BIT(reg,bit) ((reg)^=(1<<(bit)))
#define GET_BIT(reg,bit) ((((reg)>>(bit))&1U))
#define ROR_BIT(reg,bit) ((reg)=(((reg)>>(bit))|((reg)<<((sizeof(reg)*8)-(bit)))))  
#define ROL_BIT(reg,bit) ((reg)=(((reg)<<(bit))|((reg)>>((sizeof(reg)*8)-(bit)))))

#endif /* BIT_MATH_H_ */