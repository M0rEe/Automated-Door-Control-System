#include "TIMER0_interface.h"
#include "TIMER0_config.h"

static void (*InterruptHandlerOverFlow)(void) = NULL;

static void (*InterruptHandlerOnCompareMatch)(void) = NULL;

static u16 Delay = 0;

/**
 * @return void
 * @brief Stops timer from working
 */
void TIMER0_voidStopTimer(void)
{
    Clr_Bit(TCCR0, CS00);
    Clr_Bit(TCCR0, CS01);
    Clr_Bit(TCCR0, CS02);
}

/**
 * @return void
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 callback function for oncompare match
 */
void TIMER0_voidSetCallBackOnCompareMatch(void (*copy_ptr)(void))
{
    if (NULL != copy_ptr)
    {
        InterruptHandlerOnCompareMatch = copy_ptr;
    }
    else
    {
        // Error
    }
}

/**
 * @return void
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 callbackfunction for overflow
 */
void TIMER0_voidSetCallBackOverFlow(void (*copy_ptr)(void))
{
    if (NULL != copy_ptr)
    {
        InterruptHandlerOverFlow = copy_ptr;
    }
    else
    {
        // Error
    }
}

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void TIMER0_voidStartTimer(u8 copy_u8PrescalerVal)
{
    // set presacler
    switch (copy_u8PrescalerVal)
    {
    case TIMER0_FREQ_DIV_BY_1:
        Set_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case TIMER0_FREQ_DIV_BY_8:
        Clr_Bit(TCCR0, CS00);
        Set_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case TIMER0_FREQ_DIV_BY_64:
        Set_Bit(TCCR0, CS00);
        Set_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case TIMER0_FREQ_DIV_BY_256:
        Clr_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Set_Bit(TCCR0, CS02);
        break;

    case TIMER0_FREQ_DIV_BY_1024:
        Set_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Set_Bit(TCCR0, CS02);
        break;

    default:
        // Error
        break;
    }
}

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @param copy_ptr  pointer to callback function
 * @brief Initialize timer 0 with pre-defined configurations and port build configurations
 */
void TIMER0_voidInit(u8 copy_u8PrescalerVal, void (*copy_ptr)(void))
{
    // Disable module
    TIMER0_voidStopTimer();

// Select timer mode
#if (TIMER0_MODE == TIMER0_NOMRAL_MODE)

    Clr_Bit(TCCR0, WGM00);
    Clr_Bit(TCCR0, WGM01);

    // Preload value
    TCNT0 = TIMER0_PRELOAD_VALUE;
    // Enable interrupt
    TIMER0_OVER_FLOW_INTERRUPT_ENABLE();
    // setting CallBackFuntion
    TIMER0_voidSetCallBackOverFlow(copy_ptr);

#elif (TIMER0_MODE == TIMER0_CTC_MODE)

    Clr_Bit(TCCR0, WGM00);
    Set_Bit(TCCR0, WGM01);
    // Preload value
    OCR0 = TIMER0_CTC_OCR_VALUE;
    // Enable interrupt
    TIMER0_ON_COMPARE_INTERRUPT_ENABLE();
    // setting CallBackFuntion
    TIMER0_voidSetCallBackOnCompareMatch(copy_ptr);

#elif (TIMER0_MODE == TIMER0_PWM_PHASE_CORRET_MODE)

    Set_Bit(TCCR0, WGM00);
    Clr_Bit(TCCR0, WGM01);

#elif (TIMER0_MODE == TIMER0_FAST_PWM_MODE)

    Set_Bit(TCCR0, WGM00);
    Set_Bit(TCCR0, WGM01);
#else
#error NON_DEFINED_TIMER0_MODE
#endif

    // Start and Select prescaler
    TIMER0_voidStartTimer(copy_u8PrescalerVal);
}

/**
 * @return void
 * @param copy_u16MsDelay delay wanted from timer 0 to initiate
 * @brief Initialize preload timer 0 on CTC mode with specific delay
 */
void TIMER0_voidSetDelayCTCmS(u16 copy_u16MsDelay, u16 copy_u8PreScaler, u8 copy_Fcpu)
{
//TODO
    // OCR0 = TIMER0_CTC_OCR_VALUE; // based on 64 prescaler
    // // thus tick time 4us
    // Delay = copy_u16MsDelay;
    u16 ticktime_us = 0;

    // Calculate tick time in microseconds based on prescaler
    switch (copy_u8PreScaler)
    {
    case 64:
        ticktime_us = 4; // Tick time in microseconds for prescaler 64
        break;
    case 256:
        ticktime_us = 16; // Tick time in microseconds for prescaler 256
        break;
    case 1024:
        ticktime_us = 64; // Tick time in microseconds for prescaler 1024
        break;
    default:
        // Handle invalid prescaler
        return;
    }
    Delay = (copy_u16MsDelay) / (OCR0 * ticktime_us);
}

#if (TIMER0_MODE == TIMER0_NOMRAL_MODE)
ISR(TIMER0_OVF_vect)
{
    static u16 l_u16_OverFlowCounter = 0;
    l_u16_OverFlowCounter++;

    if (TIMER0_OVERFLOW_COUNTER == l_u16_OverFlowCounter)
    {
        l_u16_OverFlowCounter = 0;
        TCNT0 = TIMER0_PRELOAD_VALUE;
        if (InterruptHandlerOverFlow)
            InterruptHandlerOverFlow();
    }
}
#elif (TIMER0_MODE == TIMER0_CTC_MODE)
ISR(TIMER0_COMP_vect)
{
    static u16 l_u16_OnCompareMatchCounter = 0;
    l_u16_OnCompareMatchCounter++;

    if (Delay == l_u16_OnCompareMatchCounter)
    {
        l_u16_OnCompareMatchCounter = 0;
        TCNT0 = TIMER0_PRELOAD_VALUE;
        if (InterruptHandlerOnCompareMatch)
            InterruptHandlerOnCompareMatch();
    }
}
#elif (TIMER0_MODE == TIMER0_PWM_PHASE_CORRET_MODE)

#elif (TIMER0_MODE == TIMER0_FAST_PWM_MODE)

#endif