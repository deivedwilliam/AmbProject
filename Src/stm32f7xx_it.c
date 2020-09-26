

#include "main.h"
#include "stm32f7xx_it.h"


extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern DMA2D_HandleTypeDef hdma2d;
extern LTDC_HandleTypeDef hltdc;
extern QSPI_HandleTypeDef QSPIHandle;

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{

}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{

	while (1)
	{

	}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{

	while (1)
	{

	}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{

	while (1)
	{

	}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{

	while (1)
	{

	}
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{

}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{

}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
	HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void)
{
	HAL_LTDC_IRQHandler(&hltdc);
}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void)
{
	HAL_DMA2D_IRQHandler(&hdma2d);
}

void QUADSPI_IRQHandler(void)
{
	HAL_QSPI_IRQHandler(&QSPIHandle);
}
