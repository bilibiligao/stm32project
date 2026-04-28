#include "main.h"
#include "led.h"

/* Private variables ---------------------------------------------------------*/

static void MX_GPIO_Init(void);
static void SystemIsolation_Config(void);

/**
  * @brief  应用程序入口
  */
int main(void)
{
    /* 启用CPU Cache */
    SCB_EnableICache();
    SCB_EnableDCache();

    /* 更新系统时钟变量 (FSBL已配置时钟) */
    SystemCoreClockUpdate();

    /* 初始化HAL库 */
    HAL_Init();

    /* 再次更新系统时钟 */
    SystemCoreClockUpdate();

    /* 初始化外设 */
    MX_GPIO_Init();
    SystemIsolation_Config();

    /* 初始化LED */
    led_init();

    /* 主循环 - LED0和LED1交替闪烁, 间隔500ms */
    while (1)
    {
        LED0(0);           /* 点亮LED0 */
        LED1(1);           /* 熄灭LED1 */
        HAL_Delay(500);
        LED0(1);           /* 熄灭LED0 */
        LED1(0);           /* 点亮LED1 */
        HAL_Delay(500);
    }
}

/**
  * @brief RIF安全属性配置
  *        将LED使用的GPIO设置为安全+非特权模式
  */
static void SystemIsolation_Config(void)
{
    __HAL_RCC_RIFSC_CLK_ENABLE();

    /* PWR配置 */
    HAL_PWR_ConfigAttributes(PWR_ITEM_0, PWR_SEC_NPRIV);

    /* LED GPIO pins安全属性 */
    HAL_GPIO_ConfigPinAttributes(GPIOE, GPIO_PIN_10, GPIO_PIN_SEC | GPIO_PIN_NPRIV);
    HAL_GPIO_ConfigPinAttributes(GPIOG, GPIO_PIN_10, GPIO_PIN_SEC | GPIO_PIN_NPRIV);
}

/**
  * @brief GPIO初始化 - LED0(PG10)和LED1(PE10) 推挽输出
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 使能GPIO时钟 */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /* 初始输出高电平 (LED熄灭) */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_10, GPIO_PIN_SET);

    /* PE10 - LED1 */
    GPIO_InitStruct.Pin   = GPIO_PIN_10;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* PG10 - LED0 */
    GPIO_InitStruct.Pin   = GPIO_PIN_10;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

/**
  * @brief 错误处理 - 发生HAL错误时停在此处
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    /* 断言失败时停在此处 */
}
#endif /* USE_FULL_ASSERT */
