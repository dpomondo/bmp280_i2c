#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"
#include "aht20_i2c.h"

#define AHT20_ADDR 0x38

void aht20_init(i2c_inst_t *i2c) {
    sleep_ms(40);
    uint8_t send_buf[] = { 0xBE, 0x08, 0x00 };
    i2c_write_timeout_us(i2c, AHT20_ADDR, send_buf, 3, false, 3000);
    sleep_ms(10);
}

bool aht20_calibrated(i2c_inst_t *i2c) {
    uint8_t read_buf;
    return (i2c_read_blocking(i2c, AHT20_ADDR, &read_buf, 1, false) & AHT20_CALIBRATED);
}

void aht20_trigger_measurement(i2c_inst_t *i2c) {
    uint8_t send_buf[] = { 0xAC, 0x33, 0x00 };
    i2c_write_timeout_us(i2c, AHT20_ADDR, send_buf, 3, false, 3000);
    sleep_ms(80);
}

bool aht_read(i2c_inst_t *i2c, float *temperature, float *humidity) {
    uint8_t receive_buf[7] = { 0 };
    i2c_read_timeout_us(i2c, AHT20_ADDR, receive_buf, 7, false, 3000);

    if ((receive_buf[0] & AHT20_BUSY_FLAG) != 0) return false; // busy

    uint32_t raw_humidity = ((uint32_t)(receive_buf[1]) << 12) | (receive_buf[2] << 4) | (receive_buf[3] >> 4);
    uint32_t raw_temp = ((uint32_t)(receive_buf[3] & 0x0F) << 16) | (receive_buf[4] << 8) | receive_buf[5];

    *humidity = ((float)raw_humidity) * 100 / 1048576.0;
    *temperature = (((float)raw_temp / 1048576.0) * 200) - 50.0;

    return true;
}
