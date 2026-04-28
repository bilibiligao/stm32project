#include "led.h"

/**
 * @brief 初始化LED - 关闭LED0和LED1
 */
void led_init(void)
{
    LED0(1);    /* 关闭LED0 */
    LED1(1);    /* 关闭LED1 */
}
