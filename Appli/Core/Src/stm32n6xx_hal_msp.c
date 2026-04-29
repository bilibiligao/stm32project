#include "main.h"

void HAL_MspInit(void)
{
    HAL_PWREx_EnableVddIO2();
    HAL_PWREx_ConfigVddIORange(PWR_VDDIO2, PWR_VDDIO_RANGE_1V8);

    HAL_PWREx_EnableVddIO4();
    HAL_PWREx_ConfigVddIORange(PWR_VDDIO4, PWR_VDDIO_RANGE_3V3);
}

void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d)
{
    if (hdma2d->Instance == DMA2D)
    {
        __HAL_RCC_DMA2D_CLK_ENABLE();
    }
}

void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d)
{
    if (hdma2d->Instance == DMA2D)
    {
        __HAL_RCC_DMA2D_CLK_DISABLE();
    }
}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    if (hltdc->Instance == LTDC)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
        PeriphClkInitStruct.LtdcClockSelection = RCC_LTDCCLKSOURCE_IC16;
        PeriphClkInitStruct.ICSelection[RCC_IC16].ClockSelection = RCC_ICCLKSOURCE_PLL1;
        PeriphClkInitStruct.ICSelection[RCC_IC16].ClockDivider = 133;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RCC_LTDC_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();

        /* LTDC GPIO pins (AF14):
           PB15(G4), PB11(G6), PB12(G5), PB4(R3), PB10(G7)
           PH4(R4)
           PF8(R6), PF9(HSYNC)
           PA9(B5), PA1(G2), PA15(R5), PA10(B4), PA5(CLK),
           PA11(B3), PA2(B7), PA8(B6), PA0(G3)
           PG0(VSYNC-AF10), PG9(R7-AF14), PG13(DE-AF14)
        */
        GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_4
                            | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_1 | GPIO_PIN_15 | GPIO_PIN_10
                            | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_2 | GPIO_PIN_8
                            | GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_LCD;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LCD;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{
    if (hltdc->Instance == LTDC)
    {
        __HAL_RCC_LTDC_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_15 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_4
                              | GPIO_PIN_10);
        HAL_GPIO_DeInit(GPIOH, GPIO_PIN_4);
        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_8 | GPIO_PIN_9);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_1 | GPIO_PIN_15 | GPIO_PIN_10
                              | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_2 | GPIO_PIN_8
                              | GPIO_PIN_0);
        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0 | GPIO_PIN_9 | GPIO_PIN_13);
    }
}

void HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    if (hxspi->Instance == XSPI1)
    {
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_XSPI1;
        PeriphClkInitStruct.Xspi1ClockSelection = RCC_XSPI1CLKSOURCE_IC4;
        PeriphClkInitStruct.ICSelection[RCC_IC4].ClockSelection = RCC_ICCLKSOURCE_PLL1;
        PeriphClkInitStruct.ICSelection[RCC_IC4].ClockDivider = 6;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RCC_XSPIM_CLK_ENABLE();
        __HAL_RCC_XSPI1_CLK_ENABLE();
        __HAL_RCC_GPIOP_CLK_ENABLE();
        __HAL_RCC_GPIOO_CLK_ENABLE();

        GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_0 | GPIO_PIN_4
                            | GPIO_PIN_1 | GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
        HAL_GPIO_Init(GPIOP, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_0 | GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
        HAL_GPIO_Init(GPIOO, &GPIO_InitStruct);
    }
}

void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *hxspi)
{
    if (hxspi->Instance == XSPI1)
    {
        __HAL_RCC_XSPIM_CLK_DISABLE();
        __HAL_RCC_XSPI1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOP, GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_0 | GPIO_PIN_4
                              | GPIO_PIN_1 | GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_2);
        HAL_GPIO_DeInit(GPIOO, GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_0 | GPIO_PIN_4);
    }
}
