// System includes
#include <stm32f410rx.h>
#include <stm32f4xx.h>

// User includes
#include <user_types.h>
#include <user_functions.h>
#include <delay.h>
#include <timer.h>
#include <stdint.h>
#include <i2c.h>

// DEBUG
#include <debug_functons.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// Pin declaration
pin_struct_TypeDef scl_i2c_pb6;
pin_struct_TypeDef sda_i2c_pb7;

// Functions
void clock_init()
{
  // Enable AHB1 for GPIO
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);

  // Enable APB2 for I2C1
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
}
void pin_init()
{
  /******I2C PINS******/
  scl_i2c_pb6 = pin_setup(GPIOB, PIN6, ALTERNATE);
  // Select AF
  SET_BIT(scl_i2c_pb6.GPIOx->AFR[0], GPIO_AFRL_AFRL6_2);
  // Select open drain
  SET_BIT(scl_i2c_pb6.GPIOx->OTYPER, GPIO_OTYPER_OT_6);
  // Set to pull-up mode
  SET_BIT(scl_i2c_pb6.GPIOx->PUPDR, GPIO_PUPDR_PUPD6_0);

  sda_i2c_pb7 = pin_setup(GPIOB, PIN7, ALTERNATE);
  // Select AF
  SET_BIT(sda_i2c_pb7.GPIOx->AFR[0], GPIO_AFRL_AFRL7_2);
  // Select open drain
  SET_BIT(sda_i2c_pb7.GPIOx->OTYPER, GPIO_OTYPER_OT_7);
  // Set to pull-up mode
  SET_BIT(sda_i2c_pb7.GPIOx->PUPDR, GPIO_PUPDR_PUPD7_0);
  /********************/
}

int main(void)
{
  clock_init();
  pin_init();
  i2c1_init();

  /* Loop forever */
  while (true)
  {
  }
}
