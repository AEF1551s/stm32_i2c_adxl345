#if !defined(UART_H)
#define UART_H

#include <stm32f410rx.h>
#include <stm32f4xx.h>
#include <stdint.h>


static void uart1_set_baudrate(USART_TypeDef *USARTx)
{
    // Based on reference manual, value programmed in the baud rate register for desired transfer speed of 115,2KBs is 8,6875.
    // Converting that, we get 0x80 for mantissa and 0xB for fraction.
    USARTx->BRR = 0x80BU;
}

void uart1_init()
{
    // Configure UART baudrate for sclk = 16Mhz and 115,2kBs baud rate
    uart1_set_baudrate(USART1);

    // Configure transmit enable
    SET_BIT(USART1->CR1, USART_CR1_TE);

    // Configure receive enable
    SET_BIT(USART1->CR1, USART_CR1_RE);

    // Configure start, stop and data bits
    CLEAR_BIT(USART1->CR1, USART_CR1_M);
    CLEAR_BIT(USART1->CR2, USART_CR2_STOP_0 | USART_CR2_STOP_1);

    // Enable UART;
    SET_BIT(USART1->CR1, USART_CR1_UE);
}

void uart1_write(char ch)
{
    // Make sure the transmit data register is empty
    while (!(READ_BIT(USART1->SR, USART_SR_TXE)))
        ;

    // Write to transmit data register
    int8_t int_char = (int8_t)ch;

    USART1->DR = (int_char)&0xFF;
}

char uart1_read()
{
    // Make sure the receive data register is not empty
    while (!READ_BIT(USART1->SR, USART_SR_RXNE))
        ;

    return USART1->DR;
}

#endif // UART_H
