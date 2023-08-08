#if !defined(ADC_H)
#define ADC_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>

void analog_init(bool &continous_conv)
{
    // Set ADC channel count
    uint32_t channel_count = 0x0000U; // 1 channel to convert
    SET_BIT(ADC1->SQR1, channel_count << ADC_SQR1_L_Pos);

    // Set CH1 (PA1 pin) first in sequence.
    SET_BIT(ADC1->SQR3, 0x0001U << ADC_SQR3_SQ1_Pos);

    // Enable continous conversion mode
    if (continous_conv)
    {
        SET_BIT(ADC1->CR2, ADC_CR2_CONT);
        // ADC ON
        SET_BIT(ADC1->CR2, ADC_CR2_ADON);
        // Start conversion
        SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    }
    else
    {
        CLEAR_BIT(ADC1->CR2, ADC_CR2_CONT);
    }
}

bool check_analog_pin(pin_struct_TypeDef &pin)
{
    // Checks if pin is analog based on NUCLEO-F410RB board pinout
    if ((pin.GPIOx == GPIOA) && (pin.pinx == 0 || pin.pinx == 1 || pin.pinx == 4))
    {
        return true;
    }

    if ((pin.GPIOx == GPIOB) && (pin.pinx == 0))
    {
        return true;
    }

    if ((pin.GPIOx == GPIOC) && (pin.pinx == 0 || pin.pinx == 1))
    {
        return true;
    }

    return false;
}

uint32_t analog_read(bool &continious_conversion)
{
    if (!continious_conversion)
    {
        // ADC ON
        SET_BIT(ADC1->CR2, ADC_CR2_ADON);

        // Start conversion
        SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);

        // Set conversion not complete
        CLEAR_BIT(ADC1->SR, ADC_SR_EOC);
    }

    // Wait to conversion to be completeS
    bool ready_to_read = false;
    do
    {
        ready_to_read = READ_BIT(ADC1->SR, ADC_SR_EOC) ? true : false;
    } while (!ready_to_read);

    uint32_t read_value = ADC1->DR;

    if (!continious_conversion)
    {
        // End conversion
        CLEAR_BIT(ADC1->CR2, ADC_CR2_SWSTART);
    }

    return read_value;
}

#endif // ADC_H
