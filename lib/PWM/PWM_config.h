#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include "BitMath.h"
#include "Std_Types.h"
#include "avr/io.h"
#include "avr/interrupt.h"


#define TIMER0_PWM_PHASE_CORRET_MODE 2
#define TIMER0_FAST_PWM_MODE 4
#define PWM_MODE TIMER0_FAST_PWM_MODE


#if PWM_MODE  == TIMER0_FAST_PWM_MODE
// desired / ((ocr+1) * tick time)
#define TIMER0_FAST_PWM_OCR_VALUE    249

#define TIMER0_FAST_PWM_INVERTING   1
#define TIMER0_FAST_PWM_NON_INVERTING   2

#define TIMER0_FAST_PWM_STATE    TIMER0_FAST_PWM_NON_INVERTING

#endif

#endif //__PWM_CONFIG_H__