# STM32_i2c_xyz

This is simple excercise for STM32F410RBT6 microcontroller which is part of NUCLEO-F410RB development board.  
The goal is to learn basic principles of I2C using accelerometer module ADXL345.  

This project includes minimal headers for STM32F4xx.  
This project **does not** include any HAL header files.  
&nbsp;  
This project has been configured and generated by CubeIDE. Compiling and flashing is also done by CubeIDE.   

&nbsp;  
# Overview  
## Drivers  
Contains CMSIS drivers for STM32F4xx microcontrollers.  
## Inc  
Contains user defined header files.  
## Src  
Contains user defined source files.  

&nbsp;  
# Prerequisites
## Linux based systems  
* CubeIDE installed. See ` https://www.st.com/en/development-tools/stm32cubeide.html`.  
&nbsp;  
# Build  
Use CubeIDE to build and flash the NUCLEO development board.

## TODO: 
Sometimes there is a problem, where I2C line stays busy. The crude fix is to reconnect the ADXL345 module before adxl_init() runs.  
I believe it is fixable by adding a timout, and restarting the init function, possibly setting some software reset bit in adxl.
