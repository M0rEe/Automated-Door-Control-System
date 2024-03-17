#ifndef __TIMER1_INTERFACE_H__
#define __TIMER1_INTERFACE_H__

#include "BitMath.h"
#include "Std_Types.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define TIMER1_FREQ_DIV_BY_1 1
#define TIMER1_FREQ_DIV_BY_8 2
#define TIMER1_FREQ_DIV_BY_64 3
#define TIMER1_FREQ_DIV_BY_256 4
#define TIMER1_FREQ_DIV_BY_1024 5


void TIMER1_voidInit(u8 copy_u8PrescalerValue);

void TIMER1_voidStartTimer(u8 copy_u8PrescalerValue);

void TIMER1_voidStopTimer(void);



#endif //__TIMER1_INTERFACE_H__