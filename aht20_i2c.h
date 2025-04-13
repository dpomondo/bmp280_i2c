#ifndef AHT20_I2C_H
#define AHT20_I2C_H

#include <stdint.h>
#include "hardware/i2c.h"

#define AHT20_ADDRESS     0x38
#define AHT10_CALIBRATE_COMMAND 0xE1
#define AHT20_CALIBRATE_COMMAND 0xBE
#define AHT20_TRIGGER_MEAS_COMMAND 0xAC
#define AHT20_BUSY_FLAG   0x80
#define AHT20_CALIBRATED  0x08


extern void aht20_init(i2c_inst_t *i2c);
// extern int aht20_loop_while_busy();
extern bool aht20_calibrated(i2c_inst_t *i2c);
extern void aht20_trigger_measurement(i2c_inst_t *i2c);
extern bool aht_read(i2c_inst_t *i2c, float *temperature, float *humidity);
// extern float aht20_return_temp();
// extern float aht20_return_humidity();

#endif // !AHT20_I2C
