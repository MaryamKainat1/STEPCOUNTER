#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <math.h>

#define I2C_NODE DT_NODELABEL(i2c0)

#define LIS2DW12_ADDR     0x18

#define CTRL1             0x20
#define CTRL6             0x25

#define OUT_X_L           0x28

#define STEP_THRESHOLD    18000
#define RESET_THRESHOLD   16000

int main(void)
{
    const struct device *i2c = DEVICE_DT_GET(I2C_NODE);

    if (!device_is_ready(i2c))
    {
        printk("I2C not ready!\n");
        return 0;
    }

    /* Configure LIS2DW12 */
    uint8_t ctrl1[2] = {CTRL1, 0x40};   // 50 Hz
    i2c_write(i2c, ctrl1, 2, LIS2DW12_ADDR);

    uint8_t ctrl6[2] = {CTRL6, 0x00};   // ±2g
    i2c_write(i2c, ctrl6, 2, LIS2DW12_ADDR);

    printk("LIS2DW12 Step Counter Started\n");

    int steps = 0;
    bool step_detected = false;
    int64_t last_step_time = 0;

    while (1)
    {
        uint8_t reg = OUT_X_L | 0x80;
        uint8_t data[6];

        if (i2c_write_read(i2c,
                           LIS2DW12_ADDR,
                           &reg,
                           1,
                           data,
                           6) == 0)
        {
            int16_t x = (int16_t)((data[1] << 8) | data[0]);
            int16_t y = (int16_t)((data[3] << 8) | data[2]);
            int16_t z = (int16_t)((data[5] << 8) | data[4]);

            float magnitude = sqrt((float)x * x +
                                   (float)y * y +
                                   (float)z * z);

            if (magnitude > STEP_THRESHOLD &&
                !step_detected &&
                (k_uptime_get() - last_step_time) > 300)
            {
                steps++;
                step_detected = true;
                last_step_time = k_uptime_get();

                printk("Step Detected!\n");
            }

            if (magnitude < RESET_THRESHOLD)
            {
                step_detected = false;
            }

            printk("X = %d\n", x);
            printk("Y = %d\n", y);
            printk("Z = %d\n", z);
            printk("Magnitude = %.2f\n", magnitude);
            printk("Total Steps = %d\n", steps);
            printk("----------------------------\n");
        }
        else
        {
            printk("Read Error!\n");
        }

        k_msleep(100);
    }
}
