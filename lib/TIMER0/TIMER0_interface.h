#ifndef __TIMER0_INTERFACE_H__
#define __TIMER0_INTERFACE_H__

#include "Std_Types.h"

#define TIMER0_FREQ_DIV_BY_1 1
#define TIMER0_FREQ_DIV_BY_8 2
#define TIMER0_FREQ_DIV_BY_64 3
#define TIMER0_FREQ_DIV_BY_256 4
#define TIMER0_FREQ_DIV_BY_1024 5

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 with pre-defined configurations and port build configurations
 */
void TIMER0_voidInit(u8 copy_u8PrescalerVal, void (*copy_ptr)(void));

/**
 * @return void
 * @brief Stops timer from working
 */
void TIMER0_voidStopTimer(void);

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale 
 */
void TIMER0_voidStartTimer(u8 copy_u8PrescalerVal);

/**
 * @return void
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 callbackfunction for overflow
 */
void TIMER0_voidSetCallBackOverFlow(void (*copy_ptr)(void));

/**
 * @return void
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 callback function for oncompare match 
 */
void TIMER0_voidSetCallBackOnCompareMatch(void (*copy_ptr)(void));

/**
 * @return void
 * @param copy_u16MsDelay delay wanted from timer 0 to initiate
 * @brief Initialize preload timer 0 on CTC mode with specific delay
 */
void TIMER0_voidSetDelayCTCmS(u16 copy_u16MsDelay,u16 copy_u8PreScaler,u8 copy_Fcpu);

#endif //__TIMER0_INTERFACE_H__