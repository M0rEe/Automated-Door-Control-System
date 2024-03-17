#ifndef __PWM_INTERFACE_H__
#define __PWM_INTERFACE_H__

#include "PWM_config.h"

#define PWM_FREQ_DIV_BY_1 1
#define PWM_FREQ_DIV_BY_8 2
#define PWM_FREQ_DIV_BY_64 3
#define PWM_FREQ_DIV_BY_256 4
#define PWM_FREQ_DIV_BY_1024 5

void PWM_voidInitChannel0(void);
void PWM_voidGenerateOnChannel0(u8 copy_u8DutyCycle, u8 copy_u8PrescalerVal);

/**
 * @return void
 * @brief Stops timer from working
 */
void PWM_voidStopTimer(void);

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void PWM_voidStartTimer(u8 copy_u8PrescalerVal);

#endif //__PWM_INTERFACE_H__