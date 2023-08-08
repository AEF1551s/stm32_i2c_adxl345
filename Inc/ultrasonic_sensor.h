#if !defined(ULTRASONIC_SENSOR_H)
#define ULTRASONIC_SENSOR_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>
#include <timer.h>
#include <delay.h>
#include <user_functions.h>
#include <user_types.h>
#include <stdint.h>

// TODO: Enable floating point
//FIXME: Somewhere 8cm or (8*58)uS additional are being added to input echo signal. Across all distance ranges. Sometimes
int us_read_pb11_distance(pin_struct_TypeDef &trig_pin)
{
    int timestamp = 0;

    digital_write(trig_pin, HIGH);
    delay_ms(1);
    digital_write(trig_pin, LOW);

    // Wait for first triger. High polarity
    while (!READ_BIT(TIM5->SR, TIM_SR_CC4IF))
        ;

    TIM5->CNT = 0U;
    // Second trigger. Low polarity while first trigger is set.
    while (!READ_BIT(TIM5->SR, TIM_SR_CC4OF))
        ;

    // Read time interval and clear IF and OF flags
    timestamp = TIM5->CCR4;
    //Timeout condition
    // if (timestamp >38000)
    // {
    //     return 0;
    // }
    
    CLEAR_BIT(TIM5->SR, TIM_SR_CC4OF);

    // Minimum cycle time is no less then 50ms
    delay_ms(60);

    return timestamp;
}
#endif // ULTRASONIC_SENSOR_H
