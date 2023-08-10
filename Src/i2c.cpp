#if !defined(I2C_CPP)
#define I2C_CPP

#include "i2c.h"

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

static inline void I2C1_start_condition()
{
    // Generate start condition
    SET_BIT(I2C1->CR1, I2C_CR1_START);

    // Wait until start flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB))
        ;
}

static inline void I2C1_stop_condition()
{
    // Generate STOP after data is received
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);
}

static inline void I2C1_stop_condition_wait_rxne()
{
    I2C1_stop_condition();

    // Wait until RXNE flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE))
        ;
}

static inline void I2C1_clear_addr_read_sr2()
{
    // Clear ADDR flag by reading SR2 after SR1 has been read
    sr2_read = I2C1->SR2;
}

static inline void I2C1_send_addr_rw(char addr, I2C_RW rw)
{
    WRITE_REG(I2C1->DR, addr << 1 | rw);

    // Wait until addr flag is set
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR))
        ;

    I2C1_clear_addr_read_sr2();
}

static inline void I2C1_send_data(char data)
{
    // Wait until transmit is empty
    while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE))
        ;

    // Send data
    WRITE_REG(I2C1->DR, data);

    // Wait until transmit is empty
    while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE))
        ;
}

static inline char I2C1_get_data_dr()
{
    return I2C1->DR;
}

static inline void I2C1_enable_ack()
{
    // Enable ACK
    SET_BIT(I2C1->CR1, I2C_CR1_ACK);
}

static inline void I2C1_disable_ack()
{
    // Disable ACK
    CLEAR_BIT(I2C1->CR1, I2C_CR1_ACK);
}

void I2C1_byte_read(char saddr, char maddr, char *data)
{
    // TODO: Add timeout
    // Wait until not busy
    while (READ_BIT(I2C1->SR2, I2C_SR2_BUSY))
        ;

    I2C1_start_condition();

    I2C1_send_addr_rw(saddr, WRITE);

    I2C1_clear_addr_read_sr2();

    I2C1_send_data(maddr);

    // Restart condition
    I2C1_start_condition();

    I2C1_send_addr_rw(saddr, READ);

    I2C1_disable_ack();

    I2C1_clear_addr_read_sr2();

    I2C1_stop_condition_wait_rxne();

    *data = I2C1_get_data_dr();
    data++;
}

void I2C1_burst_read(char saddr, char maddr, uint32_t n, char *data)
{
    /* Wait until bus not busy */
    while (I2C1->SR2 & (I2C_SR2_BUSY))
        ;

    I2C1_start_condition();

    I2C1_send_addr_rw(saddr, WRITE);

    /*Send memory address */
    I2C1_send_data(maddr);

    // Repeated start condition
    I2C1_start_condition();

    I2C1_send_addr_rw(saddr, READ);

    I2C1_enable_ack();

    while (n > 0U)
    {
        /*if one byte*/
        if (n == 1U)
        {
            I2C1_disable_ack();

            I2C1_stop_condition_wait_rxne();

            /* Read data from DR */
            *data = I2C1_get_data_dr();
            data++;
            break;
        }
        else
        {
            /* Wait until RXNE flag is set */
            while (!(I2C1->SR1 & I2C_SR1_RXNE))
                ;

            // TODO: CHECK DATA POINTER
            /* Read data from DR */
            (*data++) = I2C1_get_data_dr();

            n--;
        }
    }
}

void I2C1_burst_write(char saddr, char maddr, uint32_t n, char *data)
{
    /* Wait until bus not busy */
    while (I2C1->SR2 & (I2C_SR2_BUSY))
    {
    }

    I2C1_start_condition();

    I2C1_send_addr_rw(saddr, WRITE);

    /*Send memory address */
    I2C1_send_data(maddr);

    for (uint32_t i = 0; i < n; i++)
    {

        /* Wait until data register empty */
        while (!(I2C1->SR1 & (I2C_SR1_TXE)))
            ;

        /* Transmit memory address */
        I2C1->DR = *data++;
    }

    /* Wait until transfer finished */
    while (!(I2C1->SR1 & (I2C_SR1_BTF)))
        ;

    I2C1_stop_condition();
}

#endif // I2C_CPP
