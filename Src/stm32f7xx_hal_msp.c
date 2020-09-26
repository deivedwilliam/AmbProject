#include "main.h"

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }

}

/**
* @brief DMA2D MSP Initialization
* This function configures the hardware resources used in this example
* @param hdma2d: DMA2D handle pointer
* @retval None
*/
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspInit 0 */

  /* USER CODE END DMA2D_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
  /* USER CODE BEGIN DMA2D_MspInit 1 */

  /* USER CODE END DMA2D_MspInit 1 */
  }

}

/**
* @brief DMA2D MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hdma2d: DMA2D handle pointer
* @retval None
*/
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspDeInit 0 */

  /* USER CODE END DMA2D_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();
  /* USER CODE BEGIN DMA2D_MspDeInit 1 */

  /* USER CODE END DMA2D_MspDeInit 1 */
  }

}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }

}

/**
* @brief I2S MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2s: I2S handle pointer
* @retval None
*/
void HAL_I2S_MspInit(I2S_HandleTypeDef* hi2s)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2s->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**I2S1 GPIO Configuration    
    PA4     ------> I2S1_WS
    PA5     ------> I2S1_CK
    PD7     ------> I2S1_SD 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }

}

/**
* @brief I2S MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2s: I2S handle pointer
* @retval None
*/
void HAL_I2S_MspDeInit(I2S_HandleTypeDef* hi2s)
{
  if(hi2s->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**I2S1 GPIO Configuration    
    PA4     ------> I2S1_WS
    PA5     ------> I2S1_CK
    PD7     ------> I2S1_SD 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_7);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }

}

/**
* @brief JPEG MSP Initialization
* This function configures the hardware resources used in this example
* @param hjpeg: JPEG handle pointer
* @retval None
*/
void HAL_JPEG_MspInit(JPEG_HandleTypeDef* hjpeg)
{
  if(hjpeg->Instance==JPEG)
  {
  /* USER CODE BEGIN JPEG_MspInit 0 */

  /* USER CODE END JPEG_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_JPEG_CLK_ENABLE();
  /* USER CODE BEGIN JPEG_MspInit 1 */

  /* USER CODE END JPEG_MspInit 1 */
  }

}

/**
* @brief JPEG MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hjpeg: JPEG handle pointer
* @retval None
*/
void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef* hjpeg)
{
  if(hjpeg->Instance==JPEG)
  {
  /* USER CODE BEGIN JPEG_MspDeInit 0 */

  /* USER CODE END JPEG_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_JPEG_CLK_DISABLE();
  /* USER CODE BEGIN JPEG_MspDeInit 1 */

  /* USER CODE END JPEG_MspDeInit 1 */
  }

}

/**
* @brief LTDC MSP Initialization
* This function configures the hardware resources used in this example
* @param hltdc: LTDC handle pointer
* @retval None
*/
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hltdc->Instance==LTDC)
  {

	  /* USER CODE BEGIN LTDC_MspInit 0 */

	   /* USER CODE END LTDC_MspInit 0 */
	     /* Peripheral clock enable */
	     __HAL_RCC_LTDC_CLK_ENABLE();

	     __HAL_RCC_GPIOE_CLK_ENABLE();
	     __HAL_RCC_GPIOI_CLK_ENABLE();
	     __HAL_RCC_GPIOF_CLK_ENABLE();
	     __HAL_RCC_GPIOH_CLK_ENABLE();
	     __HAL_RCC_GPIOG_CLK_ENABLE();
	     /**LTDC GPIO Configuration
	     PE5     ------> LTDC_G0
	     PE6     ------> LTDC_G1
	     PI9     ------> LTDC_VSYNC
	     PI10     ------> LTDC_HSYNC
	     PF10     ------> LTDC_DE
	     PH2     ------> LTDC_R0
	     PH3     ------> LTDC_R1
	     PH8     ------> LTDC_R2
	     PH9     ------> LTDC_R3
	     PH10     ------> LTDC_R4
	     PH11     ------> LTDC_R5
	     PH12     ------> LTDC_R6
	     PG6     ------> LTDC_R7
	     PG7     ------> LTDC_CLK
	     PH13     ------> LTDC_G2
	     PH14     ------> LTDC_G3
	     PH15     ------> LTDC_G4
	     PI0     ------> LTDC_G5
	     PI1     ------> LTDC_G6
	     PI2     ------> LTDC_G7
	     PG10     ------> LTDC_B2
	     PG11     ------> LTDC_B3
	     PG12     ------> LTDC_B1
	     PG14     ------> LTDC_B0
	     PI4     ------> LTDC_B4
	     PI5     ------> LTDC_B5
	     PI6     ------> LTDC_B6
	     PI7     ------> LTDC_B7
	     */
	     GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
	     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	     GPIO_InitStruct.Pull = GPIO_NOPULL;
	     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	     GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
	     HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	     GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
	                           |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
	                           |GPIO_PIN_7;
	     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	     GPIO_InitStruct.Pull = GPIO_NOPULL;
	     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	     GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
	     HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

	     GPIO_InitStruct.Pin = GPIO_PIN_10;
	     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	     GPIO_InitStruct.Pull = GPIO_NOPULL;
	     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	     GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
	     HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	     GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_9
	                           |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
	                           |GPIO_PIN_14|GPIO_PIN_15;
	     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	     GPIO_InitStruct.Pull = GPIO_NOPULL;
	     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	     GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
	     HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	     GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
	                           |GPIO_PIN_12|GPIO_PIN_14;
	     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	     GPIO_InitStruct.Pull = GPIO_NOPULL;
	     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	     GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
	     HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  }

}

/**
* @brief LTDC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hltdc: LTDC handle pointer
* @retval None
*/
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
  if(hltdc->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();
  
    /**LTDC GPIO Configuration    
    PE5     ------> LTDC_G0
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PC0     ------> LTDC_R5
    PH2     ------> LTDC_R0
    PH3     ------> LTDC_R1
    PB0     ------> LTDC_G1
    PH8     ------> LTDC_R2
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PA10     ------> LTDC_B1
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG10     ------> LTDC_B2
    PG11     ------> LTDC_B3
    PG14     ------> LTDC_B0
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1 
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_9 
                          |GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_14);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }

}


/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
	if(hrtc->Instance==RTC)
	{
		/* Peripheral clock enable */
		__HAL_RCC_RTC_ENABLE();
	}
}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
	if(hrtc->Instance==RTC)
	{
		/* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();
	}
}

/**
* @brief SD MSP Initialization
* This function configures the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hsd->Instance==SDMMC1)
	{
		/* Peripheral clock enable */
		__HAL_RCC_SDMMC1_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SDMMC1 GPIO Configuration
		PC8     ------> SDMMC1_D0
		PC9     ------> SDMMC1_D1
		PC10     ------> SDMMC1_D2
		PC11     ------> SDMMC1_D3
		PC12     ------> SDMMC1_CK
		PD2     ------> SDMMC1_CMD
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
							  |GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	}

}

/**
* @brief SD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
	if(hsd->Instance==SDMMC1)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SDMMC1_CLK_DISABLE();

		/**SDMMC1 GPIO Configuration
		PC8     ------> SDMMC1_D0
		PC9     ------> SDMMC1_D1
		PC10     ------> SDMMC1_D2
		PC11     ------> SDMMC1_D3
		PC12     ------> SDMMC1_CK
		PD2     ------> SDMMC1_CMD
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
						  |GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
	}
}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hspi->Instance==SPI2)
	{
		/* Peripheral clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SPI2 GPIO Configuration
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI
		PD3     ------> SPI2_SCK
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
	if(hspi->Instance==SPI2)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration
		PB14     ------> SPI2_MISO
		PB15     ------> SPI2_MOSI
		PD3     ------> SPI2_SCK
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14|GPIO_PIN_15);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3);
	}
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct ={0};
	if (FMC_Initialized)
	{
		return;
	}
	FMC_Initialized = 1;

	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();

	/** FMC GPIO Configuration
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC2   ------> FMC_SDNE0
	PC3   ------> FMC_SDCKE0
	PH5   ------> FMC_SDNWE
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	PE0   ------> FMC_NBL0
	PE1   ------> FMC_NBL1
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram)
{
	HAL_FMC_MspInit();
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void)
{
    if (FMC_DeInitialized)
    {
    	return;
    }
    FMC_DeInitialized = 1;
    /* Peripheral clock enable */
    __HAL_RCC_FMC_CLK_DISABLE();
  
	/** FMC GPIO Configuration
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC2   ------> FMC_SDNE0
	PC3   ------> FMC_SDCKE0
	PH5   ------> FMC_SDNWE
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	PE0   ------> FMC_NBL0
	PE1   ------> FMC_NBL1
	*/
	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_2|GPIO_PIN_3);

	HAL_GPIO_DeInit(GPIOH, GPIO_PIN_5);

	HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram)
{
	HAL_FMC_MspDeInit();
}

static uint32_t SAI1_client =0;

void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* SAI1 */
	if(hsai->Instance==SAI1_Block_A)
	{
		/* Peripheral clock enable */
		if (SAI1_client == 0)
		{
			__HAL_RCC_SAI1_CLK_ENABLE();
		}
		SAI1_client ++;

		/**SAI1_A_Block_A GPIO Configuration
		PE6     ------> SAI1_SD_A
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	}
}

void HAL_SAI_MspDeInit(SAI_HandleTypeDef* hsai)
{
	/* SAI1 */
	if(hsai->Instance==SAI1_Block_A)
	{
		SAI1_client --;
		if(SAI1_client == 0)
		{
			/* Peripheral clock disable */
			__HAL_RCC_SAI1_CLK_DISABLE();
		}

		/**SAI1_A_Block_A GPIO Configuration
		PE6     ------> SAI1_SD_A
		*/
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_6);
	}
}
