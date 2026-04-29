#ifndef STM32N6xx_HAL_CONF_H
#define STM32N6xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* ########################## Module Selection ############################## */
#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_RIF_MODULE_ENABLED
#define HAL_DMA2D_MODULE_ENABLED
#define HAL_LTDC_MODULE_ENABLED
#define HAL_XSPI_MODULE_ENABLED

/* ########################## Oscillator Values ############################# */
#if !defined(HSE_VALUE)
#define HSE_VALUE  48000000UL
#endif

#if !defined(HSI_VALUE)
#define HSI_VALUE  64000000UL
#endif

#if !defined(MSI_VALUE)
#define MSI_VALUE   4000000UL
#endif

#if !defined(LSE_VALUE)
#define LSE_VALUE     32768UL
#endif

#if !defined(LSI_VALUE)
#define LSI_VALUE     32000UL
#endif

#if !defined(HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT  100UL
#endif

#if !defined(LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT  5000UL
#endif

#if !defined(EXTERNAL_I2S_CLOCK_VALUE)
#define EXTERNAL_I2S_CLOCK_VALUE  12288000UL
#endif

/* ########################## System Configuration ########################## */
#define VDD_VALUE           3300UL
#define TICK_INT_PRIORITY   15U
#define USE_RTOS            0U

/* ########################## Assert Selection ############################## */
/* #define USE_FULL_ASSERT  1U */

/* ################## Register callback feature configuration ############### */
#define USE_HAL_GPIO_REGISTER_CALLBACKS         0U
#define USE_HAL_EXTI_REGISTER_CALLBACKS         0U
#define USE_HAL_DMA_REGISTER_CALLBACKS          0U
#define USE_HAL_RCC_REGISTER_CALLBACKS          0U
#define USE_HAL_PWR_REGISTER_CALLBACKS          0U
#define USE_HAL_CORTEX_REGISTER_CALLBACKS       0U
#define USE_HAL_RIF_REGISTER_CALLBACKS          0U
#define USE_HAL_DMA2D_REGISTER_CALLBACKS        0U
#define USE_HAL_LTDC_REGISTER_CALLBACKS         0U
#define USE_HAL_XSPI_REGISTER_CALLBACKS         0U

/* Includes ------------------------------------------------------------------*/
#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32n6xx_hal_rcc.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32n6xx_hal_gpio.h"
#endif

#ifdef HAL_RIF_MODULE_ENABLED
#include "stm32n6xx_hal_rif.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32n6xx_hal_dma.h"
#endif

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32n6xx_hal_cortex.h"
#endif

#ifdef HAL_EXTI_MODULE_ENABLED
#include "stm32n6xx_hal_exti.h"
#endif

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32n6xx_hal_pwr.h"
#endif

#ifdef HAL_DMA2D_MODULE_ENABLED
#include "stm32n6xx_hal_dma2d.h"
#endif

#ifdef HAL_LTDC_MODULE_ENABLED
#include "stm32n6xx_hal_ltdc.h"
#endif

#ifdef HAL_XSPI_MODULE_ENABLED
#include "stm32n6xx_hal_xspi.h"
#endif

/* Exported macros -----------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32N6xx_HAL_CONF_H */
