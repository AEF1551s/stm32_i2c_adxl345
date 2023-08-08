#if !defined(TIMER_H)
#define TIMER_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>

// #define APB1_CLOCK 16000000UL
#define PRESCALER_VALUE_US_INIT 8U     // 8 cycles = 0,5uS
#define ARR_VALUE_US_INIT 2U            // 1uS total

#define PRESCALER_VALUE_US_IC 16U       // 16 cycles = 1uS
#define ARR_VALUE_US_IC 1000000U        //  1s timeout

void tim5_us_init()
{
    //  APB1 clock enable for TIM5
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
    // Set prescaler value
    TIM5->PSC = PRESCALER_VALUE_US_INIT - 1;
    // Set auto-reload value
    TIM5->ARR = ARR_VALUE_US_INIT - 1;
    // Clear counter
    TIM5->CNT = 0U;
    // Enable timer
    SET_BIT(TIM5->CR1, TIM_CR1_CEN);
}

void tim5_pb11_input_capture()
{
    //  APB1 clock enable for TIM5
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
    // Set prescaler value
    TIM5->PSC = PRESCALER_VALUE_US_IC - 1;
    // Set auto-reload value
    TIM5->ARR = ARR_VALUE_US_IC - 1;

    // Set CH4 configured as input
    SET_BIT(TIM5->CCMR2, TIM_CCMR2_CC4S_0);

    // Set polarity mode to both edges
    SET_BIT(TIM5->CCER, TIM_CCER_CC4NP | TIM_CCER_CC4P);

    // Set to capture enable
    SET_BIT(TIM5->CCER, TIM_CCER_CC4E);

    // Enable timer
    SET_BIT(TIM5->CR1, TIM_CR1_CEN);
}
#endif // TIMER_H
