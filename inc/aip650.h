/*
 * aip650.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-26     chasel            first version
 */

#ifndef __AIP650_H__
#define __AIP650_H__
#include <rtthread.h>

#define AIP650_SET_ADDR     (0x48 >> 1)
#define AIP650_GET_KEY      (0x4F >> 1)

typedef enum {
    AIP650_7_SEGMENT = 0x09,
    AIP650_8_SEGMENT = 0x01,
} E_Segment;

typedef enum {
    BRIGHTNESS_1_LEVEL = 0x01,
    BRIGHTNESS_2_LEVEL,
    BRIGHTNESS_3_LEVEL,
    BRIGHTNESS_4_LEVEL,
    BRIGHTNESS_5_LEVEL,
    BRIGHTNESS_6_LEVEL,
    BRIGHTNESS_7_LEVEL,
    BRIGHTNESS_8_LEVEL = 0x00,
} E_Bright_level;

typedef enum {
    DIG0 = (0x68 >> 1),
    DIG1 = (0x6A >> 1),
    DIG2 = (0x6C >> 1),
    DIG3 = (0x6E >> 1),
} E_Digit_Bit;

typedef enum {
    NUMBER_0 = 0x3F,
    NUMBER_1 = 0x06,
    NUMBER_2 = 0x5B,
    NUMBER_3 = 0x4F,
    NUMBER_4 = 0x66,
    NUMBER_5 = 0x6D,
    NUMBER_6 = 0x7D,
    NUMBER_7 = 0x07,
    NUMBER_8 = 0x7F,
    NUMBER_9 = 0x6F,
    MINUS    = 0x40, /* '-' */
} E_Number;

/*
 * @brief Init aip650/tm1650
 * @return If failed at -RT_ERROR, successed is RT_EOK
 */
int aip650_init(void);

/*
 * @brief Deinit aip650/tm1650
 * @return If failed at -RT_ERROR, successed is RT_EOK
 */
int aip650_deinit(void);

/*
 * @brief Set the brightness to segment
 * @param segment Set 7 or 8 segment
 * @param level The level of brightness
 * @return If failed at -RT_ERROR, successed is RT_EOK
 */
int aip650_setSegment(E_Segment segment, E_Bright_level level);

/*
 * @brief Write the number to aip650/tm1650
 * @param bit The bit of digit
 * @param number The number of the bit
 * @param is_point Set the point to the bit
 * @return If failed at -RT_ERROR, successed is RT_EOK
 */
int aip650_writeNumber(E_Digit_Bit bit, E_Number number, int is_point);

/*
 * @brief Get the key from aip650/tm1650
 * @return The result is the key table value
 */
char aip650_getKey(void);

#endif
