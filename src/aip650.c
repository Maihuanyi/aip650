/*
 * aip650.c
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-26     chasel            first version
 */

#include <rtdevice.h>

#include "aip650.h"

#define DBG_TAG "drv.qkey"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

typedef struct {
    char key;
    char array_key;
} T_KeyTable;
const T_KeyTable Key_table[] = {
    {0x44, 0x11}, {0x4C, 0x12}, {0x54, 0x13}, {0x5C, 0x14}, {0x64, 0x15}, {0x6C, 0x16}, {0x74, 0x17},
    {0x45, 0x21}, {0x4D, 0x22}, {0x55, 0x23}, {0x5D, 0x24}, {0x65, 0x25}, {0x6D, 0x26}, {0x75, 0x27},
    {0x46, 0x31}, {0x4E, 0x32}, {0x56, 0x33}, {0x5E, 0x34}, {0x66, 0x35}, {0x6E, 0x36}, {0x76, 0x37},
    {0x47, 0x41}, {0x4F, 0x42}, {0x57, 0x43}, {0x5F, 0x44}, {0x67, 0x45}, {0x6F, 0x46}, {0x77, 0x47},
};

    
static struct rt_i2c_bus_device *Aip650_dev = RT_NULL;

int aip650_init(void)
{
    struct rt_i2c_msg msgs;

    Aip650_dev = (struct rt_i2c_bus_device *) rt_device_find(PKG_AIP650_I2C_NAME);
    if (Aip650_dev == RT_NULL) {
        LOG_E("Can't find aip650/tm1650 i2c bus %s .", PKG_AIP650_I2C_NAME);
        return -RT_ERROR;
    }
    
    char data = 0x01;
    
    msgs.addr  = AIP650_SET_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = &data;
    msgs.len   = 0x01;

    /* Enable aip650/tm1650 */
    return (rt_i2c_transfer(Aip650_dev, &msgs, 0x01) > 0) ? RT_EOK : -RT_ERROR;
}

int aip650_deinit(void)
{
    struct rt_i2c_msg msgs;

    if (Aip650_dev == RT_NULL) {
        LOG_E("The aip650 device is NULL.");
        return -RT_ERROR;
    }

    char data = 0x00;

    msgs.addr  = AIP650_SET_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = &data;
    msgs.len   = 0x01;

    /* Disable aip650/tm1650 */
    int ret = rt_i2c_transfer(Aip650_dev, &msgs, 0x01);
    if (ret) {
        Aip650_dev = RT_NULL;
        return RT_EOK;
    }
    return -RT_ERROR;
}

int aip650_set_segment(E_Segment segment, E_Bright_level level)
{
    struct rt_i2c_msg msgs;

    if (Aip650_dev == RT_NULL) {
        LOG_E("The aip650 device is NULL.");
        return -RT_ERROR;
    }

    char data = (level << 4) | segment;

    msgs.addr  = AIP650_SET_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = &data;
    msgs.len   = 0x01;

    /* Set brightness level to aip650/tm1650 */
    return (rt_i2c_transfer(Aip650_dev, &msgs, 0x01) > 0) ? RT_EOK : -RT_ERROR;
}

int aip650_write_number(E_Digit_Bit bit, E_Number number, int is_point)
{
    struct rt_i2c_msg msgs;

    if (Aip650_dev == RT_NULL) {
        LOG_E("The aip650 device is NULL.");
        return -RT_ERROR;
    }

    char data = number;

    if (is_point) 
        data |= 0x80;

    msgs.addr  = bit;
    msgs.flags = RT_I2C_WR;
    msgs.buf   = &data;
    msgs.len   = 0x01;

    /* Set digit bit to aip650/tm1650 */
    return (rt_i2c_transfer(Aip650_dev, &msgs, 0x01) > 0) ? RT_EOK : -RT_ERROR;
}

char aip650_get_key(void)
{
    struct rt_i2c_msg msgs;

    if (Aip650_dev == RT_NULL) {
        LOG_E("The aip650 device is NULL.");
        return -RT_ERROR;
    }

    char key;

    msgs.addr  = AIP650_GET_KEY;
    msgs.flags = RT_I2C_RD;
    msgs.buf   = &key;
    msgs.len   = 0x01;

    /* Read key from aip650/tm1650 */
    int ret = rt_i2c_transfer(Aip650_dev, &msgs, 0x01);
    if (!ret) {
        LOG_E("Read the key from aip650/tm1650 error.");
        return -RT_ERROR;
    }

    if (0x2E == key)
        return 0x00; /* no key */

    int temp = sizeof(Key_table) / sizeof(T_KeyTable);
    for (int i = 0; i < temp; i++) {
        if (Key_table[i].key == key)
            return Key_table[i].array_key;
    }

    return 0x00; /* no key */
}

