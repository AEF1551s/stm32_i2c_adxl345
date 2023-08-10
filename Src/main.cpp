// System includes
#include <stm32f410rx.h>
#include <stm32f4xx.h>

// User includes
#include <stdint.h>
#include <adxl345_i2c.h>
#include <user_types.h>
#include <user_functions.h>

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
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);

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

uint16_t x, y, z;
// float xg, yg, zg;
extern uint8_t data_rec[6];

int main(void)
{
  clock_init();
  pin_init();
  i2c1_init();
  adxl_init();

  /* Loop forever */
  while (true)
  {
    adxl_read_values(ADXL345_REG_DATAX0);
    x = ((data_rec[1] << 8) | data_rec[0]);
    y = ((data_rec[3] << 8) | data_rec[2]);
    z = ((data_rec[5] << 8) | data_rec[4]);

    // xg = x * ADXL345_GRAVITY_EARTH;
    // yg = y * ADXL345_GRAVITY_EARTH;
    // zg = z * ADXL345_GRAVITY_EARTH;
  }
}
