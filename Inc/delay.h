#if !defined(DELAY_H)
#define DELAY_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>
#include <timer.h>

#define SYSTICK_LOAD_VAL_MS 16000UL

void delay_ms(uint32_t delay)
{
    SysTick->LOAD = SYSTICK_LOAD_VAL_MS;

    WRITE_REG(SysTick->VAL, 0UL);

    SET_BIT(SysTick->CTRL, 1U << SysTick_CTRL_CLKSOURCE_Pos);
    SET_BIT(SysTick->CTRL, 1U << SysTick_CTRL_ENABLE_Pos);

    for (uint32_t i = 0; i < delay; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
            ;
    }
}

void delay_us(uint32_t delay) // Uses TIM5
{
    for (uint32_t i = 0; i < delay; i++)
    {

        // Wait for UIF, which resets after 1uS
        while (!READ_BIT(TIM5->SR, TIM_SR_UIF))
            ;

        // Clear UIF
        CLEAR_BIT(TIM5->SR, TIM_SR_UIF);
    }
}

#endif // DELAY_H
