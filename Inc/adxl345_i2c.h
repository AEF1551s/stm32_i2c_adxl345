#if !defined(ADXL345_I2C_H)
#define ADXL345_I2C_H

#include <i2c.h>

// Register map
#define ADXL345_ADDRESS (0x53)
#define ADXL345_REG_DEVID (0x00)
#define ADXL345_REG_THRESH_TAP (0x1D) // 1
#define ADXL345_REG_OFSX (0x1E)
#define ADXL345_REG_OFSY (0x1F)
#define ADXL345_REG_OFSZ (0x20)
#define ADXL345_REG_DUR (0x21)          // 2
#define ADXL345_REG_LATENT (0x22)       // 3
#define ADXL345_REG_WINDOW (0x23)       // 4
#define ADXL345_REG_THRESH_ACT (0x24)   // 5
#define ADXL345_REG_THRESH_INACT (0x25) // 6
#define ADXL345_REG_TIME_INACT (0x26)   // 7
#define ADXL345_REG_ACT_INACT_CTL (0x27)
#define ADXL345_REG_THRESH_FF (0x28) // 8
#define ADXL345_REG_TIME_FF (0x29)   // 9
#define ADXL345_REG_TAP_AXES (0x2A)
#define ADXL345_REG_ACT_TAP_STATUS (0x2B)
#define ADXL345_REG_BW_RATE (0x2C)
#define ADXL345_REG_POWER_CTL (0x2D)
#define ADXL345_REG_INT_ENABLE (0x2E)
#define ADXL345_REG_INT_MAP (0x2F)
#define ADXL345_REG_INT_SOURCE (0x30) // A
#define ADXL345_REG_DATA_FORMAT (0x31)
#define ADXL345_REG_DATAX0 (0x32)
#define ADXL345_REG_DATAX1 (0x33)
#define ADXL345_REG_DATAY0 (0x34)
#define ADXL345_REG_DATAY1 (0x35)
#define ADXL345_REG_DATAZ0 (0x36)
#define ADXL345_REG_DATAZ1 (0x37)
#define ADXL345_REG_FIFO_CTL (0x38)
#define ADXL345_REG_FIFO_STATUS (0x39)

// Gravitational constants
// #define ADXL345_GRAVITY_SUN 273.95f
// #define ADXL345_GRAVITY_EARTH 9.80665f
// #define ADXL345_GRAVITY_MOON 1.622f
// #define ADXL345_GRAVITY_MARS 3.69f
// #define ADXL345_GRAVITY_NONE 1.00f

extern char data;
extern uint8_t data_rec[6];

typedef enum
{
    ADXL345_RANGE_16G = 0b11,
    ADXL345_RANGE_8G = 0b10,
    ADXL345_RANGE_4G = 0b01,
    ADXL345_RANGE_2G = 0b00
} adxl345_range_t;

void adxl_init();
void adxl_read_adress(uint8_t reg);
void adxl_read_values(uint8_t reg);
void adxl_write(uint8_t reg, char value);

#endif // ADXL345_I2C_H
