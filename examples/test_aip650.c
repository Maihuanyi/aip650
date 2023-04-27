#include <rtthread.h>
#include <finsh.h>

#include "aip650.h"

int test_aip650(int argn, char** argv)
{
    int ret = aip650_init();
    if (ret != RT_EOK) {
        rt_kprintf("Init the aip650 error\n");
        return -RT_ERROR; 
    }

    ret = aip650_set_segment(AIP650_8_SEGMENT, BRIGHTNESS_8_LEVEL);
    if (ret != RT_EOK) {
        rt_kprintf("Set the aip650 error\n");
        return -RT_ERROR;
    }

    rt_kprintf("Writing the number 1234 to digit led.\n");
    ret = aip650_write_number(DIG1, NUMBER_1, RT_TRUE);
    if (ret != RT_EOK) {
        rt_kprintf("Write the number 1 to aip650 error\n");
        return -RT_ERROR;
    }
    ret = aip650_write_number(DIG2, NUMBER_2, RT_TRUE);
    if (ret != RT_EOK) {
        rt_kprintf("Write the number 2 to aip650 error\n");
        return -RT_ERROR;
    }
    ret = aip650_write_number(DIG3, NUMBER_3, RT_TRUE);
    if (ret != RT_EOK) {
        rt_kprintf("Write the number 3 to aip650 error\n");
        return -RT_ERROR;
    }
    ret = aip650_write_number(DIG4, NUMBER_4, RT_TRUE);
    if (ret != RT_EOK) {
        rt_kprintf("Write the number 4 to aip650 error\n");
        return -RT_ERROR;
    }

#ifdef AIP650_TEST_KEY
    char key;
    rt_kprintf("Pleased to press the key.\n");
    do {
        key = aip650_get_key();
        rt_thread_mdelay(10);
    } while (key <= 0); /* Get one key from aip650/tm1650 */
    rt_kprintf("The key value: %02x\n", key);
    rt_kprintf("The test key is over.\n");
#endif

    return RT_EOK;
}
MSH_CMD_EXPORT(test_aip650, test aip650/tm1650);

