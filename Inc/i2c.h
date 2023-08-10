#if !defined(I2C_H)
#define I2C_H

// System includes
#include <stm32f410rx.h>
#include <stm32f4xx.h>

// Values calculated based on datasheet instructions
#define PERIPH_CLOCK_FREQ 0x10 // 16
#define I2C_100KHZ 80
#define I2C_MAX_RISE_TIME 17

static volatile uint16_t sr2_read;

typedef enum
{
    WRITE = 0U,
    READ = 1U

} I2C_RW;

void i2c1_init();
static inline void I2C1_start_condition();
static inline void I2C1_stop_condition();
static inline void I2C1_stop_condition_wait_rxne();
static inline void I2C1_clear_addr_read_sr2();
static inline void I2C1_send_addr_rw(char addr, I2C_RW rw);
static inline void I2C1_send_data(char data);
static inline char I2C1_get_data_dr(); 
static inline void I2C1_enable_ack();
static inline void I2C1_disable_ack();
void I2C1_byte_read(char saddr, char maddr, char *data);
void I2C1_burst_read(char saddr, char maddr, uint32_t n, char *data);
void I2C1_burst_write(char saddr, char maddr, uint32_t n, char *data);

#endif // I2C_H
