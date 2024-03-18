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
#if (PWM_MODE == TIMER0_FAST_PWM_MODE)
    OCR0 = TIMER0_FAST_PWM_OCR_VALUE;
#endif
}

void PWM_voidGenerateOnChannel0(u8 copy_u8DutyCycle, u8 copy_u8PrescalerVal)
{
    if (copy_u8DutyCycle <= 100)
    {
        OCR0 = (((u16)copy_u8DutyCycle * 256) / 100) - 1;
        PWM_voidStartTimer0(copy_u8PrescalerVal);
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
void PWM_voidStopTimer0(void)
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
void PWM_voidStartTimer0(u8 copy_u8PrescalerVal)
{
    PWM_voidStopTimer0();
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

void PWM_voidInitChannel1A(void)
{
    // Select fast pwm Mode
    Set_Bit(TCCR1B, WGM13);
    Set_Bit(TCCR1B, WGM12);

    Set_Bit(TCCR1A, WGM11);
    Clr_Bit(TCCR1A, WGM10);
    // Select non-Inverting mode
#if TIMER1A_FAST_PWM_STATE == TIMER1A_FAST_PWM_INVERTING
    Set_Bit(TCCR1A, COM1A0);
    Set_Bit(TCCR1A, COM1B0);

    Set_Bit(TCCR1A, COM1A1);
    Set_Bit(TCCR1A, COM1B1);
#elif TIMER1A_FAST_PWM_STATE == TIMER1A_FAST_PWM_NON_INVERTING
    Clr_Bit(TCCR1A, COM1A0);
    Clr_Bit(TCCR1A, COM1B0);

    Set_Bit(TCCR1A, COM1A1);
    Set_Bit(TCCR1A, COM1B1);
#else
    Clr_Bit(TCCR1A, COM1A0);
    Clr_Bit(TCCR1A, COM1B0);

    Clr_Bit(TCCR1A, COM1A1);
    Clr_Bit(TCCR1A, COM1B1);
#endif
}

void PWM_voidGenerateOnChannel1A(u16 copy_u16PWMFreqHZ, f32 copy_f32DutyCycle, u8 copy_u8PrescalerVal)
{
    // Frequency calculations
    ICR1 = (u16)((1000000UL / copy_u16PWMFreqHZ) / 4) - 1;
    
    // Duty cycle ratio
    OCR1A = (u16)((u32)(copy_f32DutyCycle * (ICR1 + 1)) / 100) - 1;
    
    // Select Prescaler
    PWM_voidStartTimer1A(copy_u8PrescalerVal);
}

/**
 * @return void
 * @brief Stops timer from working
 */
void PWM_voidStopTimer1A(void)
{
    Clr_Bit(TCCR1B, CS10);
    Clr_Bit(TCCR1B, CS11);
    Clr_Bit(TCCR1B, CS12);
}

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void PWM_voidStartTimer1A(u8 copy_u8PrescalerVal)
{
    PWM_voidStopTimer1A();
    switch (copy_u8PrescalerVal)
    {
    case PWM_FREQ_DIV_BY_1:
        Set_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case PWM_FREQ_DIV_BY_8:
        Clr_Bit(TCCR1B, CS10);
        Set_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case PWM_FREQ_DIV_BY_64:
        Set_Bit(TCCR1B, CS10);
        Set_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case PWM_FREQ_DIV_BY_256:
        Clr_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Set_Bit(TCCR1B, CS12);
        break;

    case PWM_FREQ_DIV_BY_1024:
        Set_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Set_Bit(TCCR1B, CS12);
        break;

    default:
        break;
    }
}
