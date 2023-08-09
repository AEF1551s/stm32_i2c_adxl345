#if !defined(I2C_H)
#define I2C_H

// System includes
#include <stm32f410rx.h>
#include <stm32f4xx.h>

// User includes
#include <user_types.h>
#include <user_functions.h>

// Values calculated based on datasheet instructions
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

    // Enable I2C1 Module
    SET_BIT(I2C1->CR1, I2C_CR1_PE);
}

static inline void I2C1_send_slave_adress(char saddr)
{
    volatile int32_t temp;

    // Wait until not busy
    while (READ_BIT(I2C1->SR2, I2C_SR2_BUSY))
        ;

    // Generate start condition
    SET_BIT(I2C1->CR1, I2C_CR1_START);

    // Wait until start flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB))
        ;

    // Transmit slave adress + write
    WRITE_REG(I2C1->DR, saddr << 1);

    // Wait until addr flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR))
        ;

    // Read SR2, after which SR1_ADDR flag is automatically reset
    temp = I2C1->SR2;
}

void I2C1_byte_read(char saddr, char maddr, char *data)
{
    volatile int32_t temp;

    I2C1_send_slave_adress(saddr);

    // Send memory address
    WRITE_REG(I2C1->DR, maddr);

    // Wait until DR is empty. Wait until transsmit data register is empty
    while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE))
        ;

    // Generate start condition
    SET_BIT(I2C1->CR1, I2C_CR1_START);

    // Wait until start flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB))
        ;

    // Transmit slave adress + read
    WRITE_REG(I2C1->DR, saddr << 1 | 1);

    // Wait until addr flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR))
        ;

    // Disable ACK
    CLEAR_BIT(I2C1->CR1, I2C_CR1_ACK);

    // Clear ADDR flag
    temp = I2C1->SR2;

    // Generate STOP after data is received
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);

    // Wait until RXNE flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE))
        ;

    // Read data from DR
    *data++ = I2C1->DR;
}

#endif // I2C_H
