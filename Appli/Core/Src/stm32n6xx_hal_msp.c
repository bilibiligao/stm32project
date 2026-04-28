#include "main.h"

/**
  * @brief HAL MSP初始化 - 配置电源(VddIO2)等
  */
void HAL_MspInit(void)
{
    HAL_PWREx_EnableVddIO2();
    HAL_PWREx_ConfigVddIORange(PWR_VDDIO2, PWR_VDDIO_RANGE_1V8);
}
