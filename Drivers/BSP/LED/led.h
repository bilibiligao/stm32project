#ifndef __LED_H
#define __LED_H

#include "main.h"

/* LED引脚定义 - 正点原子N647开发板 */
#define LED0_GPIO_PORT  GPIOG
#define LED0_GPIO_PIN   GPIO_PIN_10
#define LED1_GPIO_PORT  GPIOE
#define LED1_GPIO_PIN   GPIO_PIN_10

/* LED操作宏 - 低电平点亮, 高电平熄灭 */
#define LED0(x)  do { (x) ? \
    HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : \
    HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
} while (0)

#define LED1(x)  do { (x) ? \
    HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : \
    HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
} while (0)

#define LED0_TOGGLE()  do { HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); } while (0)
#define LED1_TOGGLE()  do { HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); } while (0)

void led_init(void);

#endif
