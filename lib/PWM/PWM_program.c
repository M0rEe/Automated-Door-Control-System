#include "PWM_interface.h"

void PWM_voidInitChannel0(void)
{
    // Select Fast PWM
    Set_Bit(TCCR0, WGM00);
    Set_Bit(TCCR0, WGM01);
    // Select non/inverting
#if TIMER0_FAST_PWM_STATE == TIMER0_FAST_PWM_INVERTING
    Set_Bit(TCCR0, COM00);
    Set_Bit(TCCR0, COM01);
#elif TIMER0_FAST_PWM_STATE == TIMER0_FAST_PWM_NON_INVERTING
    Clr_Bit(TCCR0, COM00);
    Set_Bit(TCCR0, COM01);
#else
    Clr_Bit(TCCR0, COM00);
    Clr_Bit(TCCR0, COM01);
#endif
    // Duty cycle ratio
    OCR0 = TIMER0_FAST_PWM_OCR_VALUE;
}

void PWM_voidGenerateOnChannel0(u8 copy_u8DutyCycle, u8 copy_u8PrescalerVal)
{
    if (copy_u8DutyCycle <= 100)
    {
        OCR0 = (((u16)copy_u8DutyCycle * 256) / 100) - 1;
        PWM_voidStartTimer(copy_u8PrescalerVal);
    }
    else
    {
        // Error
    }
}

/**
 * @return void
 * @brief Stops timer from working
 */
void PWM_voidStopTimer(void)
{
    Clr_Bit(TCCR0, CS00);
    Clr_Bit(TCCR0, CS01);
    Clr_Bit(TCCR0, CS02);
}

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void PWM_voidStartTimer(u8 copy_u8PrescalerVal)
{
    PWM_voidStopTimer();
    // set presacler
    switch (copy_u8PrescalerVal)
    {
    case PWM_FREQ_DIV_BY_1:
        Set_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case PWM_FREQ_DIV_BY_8:
        Clr_Bit(TCCR0, CS00);
        Set_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case PWM_FREQ_DIV_BY_64:
        Set_Bit(TCCR0, CS00);
        Set_Bit(TCCR0, CS01);
        Clr_Bit(TCCR0, CS02);
        break;

    case PWM_FREQ_DIV_BY_256:
        Clr_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Set_Bit(TCCR0, CS02);
        break;

    case PWM_FREQ_DIV_BY_1024:
        Set_Bit(TCCR0, CS00);
        Clr_Bit(TCCR0, CS01);
        Set_Bit(TCCR0, CS02);
        break;

    default:
        // Error
        break;
    }
}
