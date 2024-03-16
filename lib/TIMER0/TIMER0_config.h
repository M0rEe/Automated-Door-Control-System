#ifndef __TIMER0_CONFIG_H__
#define __TIMER0_CONFIG_H__

#include "BitMath.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define TIMER0_NOMRAL_MODE 1
#define TIMER0_PWM_PHASE_CORRET_MODE 2
#define TIMER0_CTC_MODE 3
#define TIMER0_FAST_PWM_MODE 4

#define TIMER0_MODE TIMER0_CTC_MODE

// desired / overflow time 
#define TIMER0_PRELOAD_VALUE    224
#define TIMER0_OVERFLOW_COUNTER 1952


#define TIMER0_OVER_FLOW_INTERRUPT_ENABLE() (Set_Bit(TIMSK, TOIE0))
#define TIMER0_OVER_FLOW_INTERRUPT_DISABLE() (Clr_Bit(TIMSK, TOIE0))


// desired / ((ocr+1) * tick time)
#define TIMER0_CTC_OCR_VALUE    249


#define TIMER0_ON_COMPARE_INTERRUPT_ENABLE() (Set_Bit(TIMSK, OCIE0))
#define TIMER0_ON_COMPARE_INTERRUPT_DISABLE() (Clr_Bit(TIMSK, OCIE0))


#endif //__TIMER0_CONFIG_H__