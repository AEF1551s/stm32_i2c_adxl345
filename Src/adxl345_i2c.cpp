#if !defined(ADXL345_I2C_CPP)
#define ADXL345_I2C_CPP

#include <adxl345_i2c.h>

void adxl_init(){
    //Read DEVICE_ID, should return 0xE5
    adxl_read_adress(ADXL345_REG_DEVID);

    //Set data format range to +-4g
    adxl_write(ADXL345_REG_DATA_FORMAT, ADXL345_RANGE_4G);

    //Reset all bits
    adxl_write(ADXL345_REG_POWER_CTL, 0x00);

    //Configure power control measurment bit
    adxl_write(ADXL345_REG_POWER_CTL, 0x08);

}

void adxl_read_adress(uint8_t reg)
{
    I2C1_byte_read(ADXL345_ADDRESS, reg, &data);
}

void adxl_write(uint8_t reg, char value)
{
    char data[1];
    data[0] = value;

    I2C1_burst_write(ADXL345_ADDRESS, reg, 1, data);
}

void adxl_read_values(uint8_t reg)
{
I2C1_burst_read(ADXL345_ADDRESS, reg, 6, (char*)data_rec);
}

#endif // ADXL345_I2C_CPP
