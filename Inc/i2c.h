#if !defined(I2C_H)
#define I2C_H

// System includes
#include <stm32f410rx.h>
#include <stm32f4xx.h>

// User includes
#include <user_types.h>
#include <user_functions.h>

//Values calculated based on datasheet instructions
#define PERIPH_CLOCK_FREQ 0x10 // 16
#define I2C_100KHZ 80
#define I2C_MAX_RISE_TIME 17

void i2c1_init()
{
    // Reset I2C
    SET_BIT(I2C1->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(I2C1->CR1, I2C_CR1_SWRST);

    // Set I2C peripheral clock frequency: 16MHz
    SET_BIT(I2C1->CR2, PERIPH_CLOCK_FREQ << I2C_CR2_FREQ_Pos);

    // Set I2C speed: 100kHz
    SET_BIT(I2C1->CCR, I2C_100KHZ << I2C_CCR_CCR_Pos);

    // Set maximum rise time
    SET_BIT(I2C1->TRISE, I2C_MAX_RISE_TIME << I2C_TRISE_TRISE_Pos);
    
    //Enable I2C1 Module
    SET_BIT(I2C1->CR1, I2C_CR1_PE);
}

#endif // I2C_H
