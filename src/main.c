#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"
#include "TIMER0_interface.h"
#include "PWM_interface.h"
#include "HBRIDGE_interface.h"
#include "BitMath.h"

/* Keypad Matrix */
u8 KeypadMatrix[4][4] = {
    {'7', '8', '9', 'A'},
    {'4', '5', '6', 'B'},
    {'1', '2', '3', 'C'},
    {'*', '0', '#', 'D'}};

/***
 * @return Value withen new range
 * @param X value to be mapped
 * @param in_min input range minimumm
 * @param in_max input range maximum
 * @param out_min output range minimum
 * @param out_max output range maximum
 *
 */
u16 map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max)
{
  return (u32)(x - in_min) * (u32)(out_max - out_min) / (u32)(in_max - in_min) + out_min;
}

void func(void)
{
  Tog_Bit(PORTA, PIN5);
}

int main(void)
{
  /* Initialization seciton */
  DIO_voidInitPins();
  // LCD_4_bit_voidInit();
  PWM_voidInitChannel1A();
  // PWM_voidGenerateOnChannel1A(50, 5, PWM_FREQ_DIV_BY_64);

  while (1)
  {

    PWM_voidGenerateOnChannel1A(50, 5, PWM_FREQ_DIV_BY_64);
    _delay_ms(1500);
    PWM_voidStopTimer1A();

    PWM_voidGenerateOnChannel1A(50, 7.5, PWM_FREQ_DIV_BY_64);
    _delay_ms(1500);
    PWM_voidStopTimer1A();

    PWM_voidGenerateOnChannel1A(50, 10, PWM_FREQ_DIV_BY_64);
    _delay_ms(1500);
    PWM_voidStopTimer1A();                      
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));
