#include "main.h"
#include "stm32n6xx_it.h"

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers             */
/******************************************************************************/

void NMI_Handler(void)
{
    while (1) { }
}

void HardFault_Handler(void)
{
    while (1) { }
}

void MemManage_Handler(void)
{
    while (1) { }
}

void BusFault_Handler(void)
{
    while (1) { }
}

void UsageFault_Handler(void)
{
    while (1) { }
}

void SecureFault_Handler(void)
{
    while (1) { }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

/**
  * @brief SysTick中断处理 - HAL库时基
  */
void SysTick_Handler(void)
{
    HAL_IncTick();
}
