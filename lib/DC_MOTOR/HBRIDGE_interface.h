#ifndef __HBRIDGE_INTERFACE_H__
#define __HBRIDGE_INTERFACE_H__
#include "HBRIDGE_config.h"

#define HB_CLOCKWISE 1
#define HB_COUNTER_CLOCKWISE 2

void HB_voidInit(u8 copy_MotorNumber);

void HB_voidMotorStart(u8 copy_u8Direction, u8 copy_MotorNumber);

void HB_voidMotorStop(u8 copy_MotorNumber);

void HB_voidSetMotorSpeed(u8 copy_u8DutyCycle, u8 copy_u8PWMPrescaler, u8 copy_MotorNumber);

#endif //__HBRIDGE_INTERFACE_H__