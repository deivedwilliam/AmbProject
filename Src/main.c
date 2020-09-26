#include "main.h"
#include "fatfs.h"
#include "lwip.h"
#include "app_touchgfx.h"
#include "usb_host.h"
#include "ADV7513.h"
#include "ff.h"
#include "QSPI.h"

#define BUFFER_SIZE         ((uint32_t)0x1000)
#define WRITE_READ_ADDR     ((uint32_t)0x0800)

/* Read/Write Buffers */
uint16_t aTxBuffer[BUFFER_SIZE];
uint16_t aRxBuffer[BUFFER_SIZE];
/* Status variables */
__IO uint32_t uwWriteReadStatus = 0;
/* Counter index */
uint32_t uwIndex = 0;

CRC_HandleTypeDef hcrc;
DMA2D_HandleTypeDef hdma2d;
I2C_HandleTypeDef hi2c1;
I2S_HandleTypeDef hi2s1;
JPEG_HandleTypeDef hjpeg;
LTDC_HandleTypeDef hltdc;
RTC_HandleTypeDef hrtc;
SAI_HandleTypeDef hsai_BlockA1;
SD_HandleTypeDef hsd1;
SPI_HandleTypeDef hspi2;
SDRAM_HandleTypeDef hsdram1;
ADV7513ConfigTypeDef AdvConfigStruct;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S1_Init(void);
static void MX_JPEG_Init(void);
static void MX_LTDC_Init(void);
static void MX_QUADSPI_Init(void);
static void MX_RTC_Init(void);
static void MX_SAI1_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_SPI2_Init(void);
void MX_USB_HOST_Process(void);
extern void udp_echoserver_init(void);
static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram);
static void Fill_Buffer(uint16_t *pBuffer, uint32_t uwBufferLenght, uint16_t uwOffset);
TestStatus_t SDRAM_Test(void);
uint8_t QSPI_EnableMemoryMappedMode(void);


int __io_putchar(int ch)
{
	ITM_SendChar(ch);

	return ch;
}



/**
  * @brief  Fills a buffer.
  * @param  LayerIndex: Layer index
  * @param  pDst: Pointer to destination buffer
  * @param  xSize: Buffer width
  * @param  ySize: Buffer height
  * @param  OffLine: Offset
  * @param  ColorIndex: Color index
  */
static void LL_FillBuffer(uint32_t LayerIndex, void *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t ColorIndex)
{
	/* Register to memory mode with ARGB8888 as color Mode */
//	hdma2d.Init.Mode         = DMA2D_R2M;
//	hdma2d.Init.ColorMode    = DMA2D_OUTPUT_RGB888;
//	hdma2d.Init.OutputOffset = OffLine;
//	hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_SWAP;
//	hdma2d.Instance = DMA2D;
//	hdma2d.Init.RedBlueSwap = DMA2D_RB_SWAP;
//
//	/* DMA2D Initialization */
//	if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)

		if(HAL_DMA2D_ConfigLayer(&hdma2d, LayerIndex) == HAL_OK)

			if (HAL_DMA2D_Start(&hdma2d, ColorIndex, (uint32_t)pDst, xSize, ySize) == HAL_OK)
			{
				/* Polling For DMA transfer */
				HAL_DMA2D_PollForTransfer(&hdma2d, 10);
			}


}

/**
  * @brief  Clears the whole currently active layer of LTDC.
  * @param  Color: Color of the background
  */
void BSP_LCD_Clear(uint32_t Color)
{
	/* Clear the LCD */
	LL_FillBuffer(0, (uint32_t *)(hltdc.LayerCfg[0].FBStartAdress), 640, 480, 0, Color);
}
/**
  * @brief  Configure the MPU attributes .
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

//	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU as Normal Non Cacheable for Ethernet Buffers in the SRAM2 */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = SDRAM_BANK_ADDR;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = SDRAM_BANK_ADDR;
	MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER2;
	MPU_InitStruct.BaseAddress = 0x90000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
	MPU_InitStruct.SubRegionDisable = 0x0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	MPU_InitStruct.BaseAddress = 0x90000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_16MB;
	MPU_InitStruct.SubRegionDisable = 0x0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint8_t version = 0;
	uint16_t deviceId = 0;
	QSPI_CommandTypeDef      sCommand;
	QSPI_MemoryMappedTypeDef sMemMappedCfg;

	MPU_Config();
	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();

	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CRC_Init();

	MX_FMC_Init();

	BSP_QSPI_Init();
	BSP_QSPI_EnableMemoryMappedMode();
	/* Program the SDRAM external device */
	BSP_SDRAM_Initialization_Sequence(&hsdram1);

	/*##-2- SDRAM memory read/write access */
	if(SDRAM_Test() != PASSED)
	{
		Error_Handler();
	}

	/* Initialize QuadSPI structures ------------------------------------------- */

	MX_I2C1_Init();
	MX_DMA2D_Init();
	MX_LTDC_Init();

	//
	//	//MX_USB_HOST_Init();
	MX_FATFS_Init();

	ADV7513_Init();
	version = ADV7513_ReadDeviceVersion();
	deviceId = ADV7513_GetDeviceID();
	printf("Device version %u\n", version);
	printf("Device Id = %x\n", deviceId);
	MX_TouchGFX_Init();

	__HAL_LTDC_LAYER_ENABLE(&hltdc, 0);

	while (1)
	{
//		BSP_LCD_Clear(LCD_COLOR_RED);
//		HAL_Delay(2000);
//		BSP_LCD_Clear(LCD_COLOR_GREEN);
//		HAL_Delay(2000);
//		BSP_LCD_Clear(LCD_COLOR_BLUE);
//		HAL_Delay(2000);

		MX_TouchGFX_Process();
		HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
		HAL_Delay(50);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/** Configure LSE Drive Capability
	*/
	HAL_PWR_EnableBkUpAccess();
	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 400;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	*/
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_RTC
							  |RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_I2C1
							  |RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_I2S
							  |RCC_PERIPHCLK_CLK48;
	PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
	PeriphClkInitStruct.PLLI2S.PLLI2SP = RCC_PLLP_DIV2;
	PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
	PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
	PeriphClkInitStruct.PLLSAI.PLLSAIQ = 8;
	PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
	PeriphClkInitStruct.PLLI2SDivQ = 1;
	PeriphClkInitStruct.PLLSAIDivQ = 1;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	PeriphClkInitStruct.I2sClockSelection = RCC_I2SCLKSOURCE_PLLI2S;
	PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI;
	PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
	PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
	if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
}

TestStatus_t SDRAM_Test(void)
{
	/* Fill the buffer to write */
	Fill_Buffer(aTxBuffer, BUFFER_SIZE, 0x2442);

	/* Write data to the SDRAM memory */
	for(uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++)
	{
		*(__IO uint16_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR + 2*uwIndex) = aTxBuffer[uwIndex];
	}

	/* Read back data from the SDRAM memory */
	for(uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++)
	{
		aRxBuffer[uwIndex] = *(__IO uint16_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR + 2*uwIndex);
	}

	/*##-3- Checking data integrity ############################################*/

	for(uwIndex = 0; (uwIndex < BUFFER_SIZE) && (uwWriteReadStatus == 0); uwIndex++)
	{
		if(aRxBuffer[uwIndex] != aTxBuffer[uwIndex])
		{
			uwWriteReadStatus++;
		}
	}

	if(uwWriteReadStatus != PASSED)
	{
		return FAILED;
	}

	return PASSED;
}
/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{
	hdma2d.Instance = DMA2D;
	hdma2d.Init.Mode = DMA2D_M2M;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
	hdma2d.Init.OutputOffset = 0;
	hdma2d.Init.RedBlueSwap = DMA2D_RB_SWAP;

	hdma2d.LayerCfg[1].InputOffset = 0;
	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputAlpha = 0;
	hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
	hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_SWAP;
	if(HAL_DMA2D_Init(&hdma2d) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
	{
		Error_Handler();
	}

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0xA010131A;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Analogue filter
	*/
	if(HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLED) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Digital filter
	*/
	if(HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 5) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief I2S1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S1_Init(void)
{

  /* USER CODE BEGIN I2S1_Init 0 */

  /* USER CODE END I2S1_Init 0 */

  /* USER CODE BEGIN I2S1_Init 1 */

  /* USER CODE END I2S1_Init 1 */
  hi2s1.Instance = SPI1;
  hi2s1.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s1.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s1.Init.DataFormat = I2S_DATAFORMAT_24B;
  hi2s1.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s1.Init.AudioFreq = I2S_AUDIOFREQ_48K;
  hi2s1.Init.CPOL = I2S_CPOL_LOW;
  hi2s1.Init.ClockSource = I2S_CLOCK_PLL;
  if (HAL_I2S_Init(&hi2s1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S1_Init 2 */

  /* USER CODE END I2S1_Init 2 */

}

/**
  * @brief JPEG Initialization Function
  * @param None
  * @retval None
  */
static void MX_JPEG_Init(void)
{
	hjpeg.Instance = JPEG;
	if(HAL_JPEG_Init(&hjpeg) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{
	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	hltdc.Instance = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc.Init.HorizontalSync = 95;
	hltdc.Init.VerticalSync = 1;
	hltdc.Init.AccumulatedHBP = 143;
	hltdc.Init.AccumulatedVBP = 32;
	hltdc.Init.AccumulatedActiveW = 783;
	hltdc.Init.AccumulatedActiveH = 512;
	hltdc.Init.TotalWidth = 799;
	hltdc.Init.TotalHeigh = 523;
	hltdc.Init.Backcolor.Blue = 40;
	hltdc.Init.Backcolor.Green = 80;
	hltdc.Init.Backcolor.Red = 225;
	if(HAL_LTDC_Init(&hltdc) != HAL_OK)
	{
		Error_Handler();
	}
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = 640;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = 480;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	pLayerCfg.FBStartAdress = 0xC0000000;
	pLayerCfg.ImageWidth = 640;
	pLayerCfg.ImageHeight = 480;
	pLayerCfg.Backcolor.Blue = 255;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if(HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{
	/** Initialize RTC Only
	*/
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if(HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief SAI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SAI1_Init(void)
{

  /* USER CODE BEGIN SAI1_Init 0 */

  /* USER CODE END SAI1_Init 0 */

  /* USER CODE BEGIN SAI1_Init 1 */

  /* USER CODE END SAI1_Init 1 */
  hsai_BlockA1.Instance = SAI1_Block_A;
  hsai_BlockA1.Init.Protocol = SAI_SPDIF_PROTOCOL;
  hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_TX;
  hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
  hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_48K;
  hsai_BlockA1.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
  if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAI1_Init 2 */

  /* USER CODE END SAI1_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{
	FMC_SDRAM_TimingTypeDef SdramTiming = {0};

	/** Perform the SDRAM1 memory initialization sequence
	*/
	hsdram1.Instance = FMC_SDRAM_DEVICE;
	/* hsdram1.Init */
	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_10;
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
	/* SdramTiming */
	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 7;
	SdramTiming.SelfRefreshTime = 4;
	SdramTiming.RowCycleDelay = 7;
	SdramTiming.WriteRecoveryTime = 2;
	SdramTiming.RPDelay = 2;
	SdramTiming.RCDDelay = 2;

	if(HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
	{
		Error_Handler( );
	}
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, NRF24_CSN_Pin|NRF24_CE_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, LED_STATUS_Pin|GPIO_PIN_5, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(PD_GPIO_Port, PD_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(PD_GPIO_Port, PD_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : NRF24_CSN_Pin NRF24_CE_Pin */
	GPIO_InitStruct.Pin = NRF24_CSN_Pin|NRF24_CE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pin : NRF24_IRQ_Pin */
	GPIO_InitStruct.Pin = NRF24_IRQ_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(NRF24_IRQ_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : SD_DETECT_Pin PD4 */
	GPIO_InitStruct.Pin = SD_DETECT_Pin|GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : LED_STATUS_Pin PD5 */
	GPIO_InitStruct.Pin = LED_STATUS_Pin|GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pin : PD_Pin */
	GPIO_InitStruct.Pin = PD_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(PD_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : INT_HDMI_Pin */
	GPIO_InitStruct.Pin = INT_HDMI_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(INT_HDMI_GPIO_Port, &GPIO_InitStruct);

}

/**
  * @brief  Perform the SDRAM external memory initialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
static void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram)
{
	FMC_SDRAM_CommandTypeDef Command = {0};
	__IO uint32_t tmpmrd =0;
	/* Step 3:  Configure a clock configuration enable command */
	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 4: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	HAL_Delay(1);

	/* Step 5: Configure a PALL (precharge all) command */
	Command.CommandMode = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 6 : Configure a Auto-Refresh command */
	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 8;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 7: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_2           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	//hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));
	HAL_SDRAM_ProgramRefreshRate(hsdram, 0x0603);
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint16_t *pBuffer, uint32_t uwBufferLenght, uint16_t uwOffset)
{
	uint32_t tmpIndex = 0;

	/* Put in global buffer different values */
	for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
	{
		pBuffer[tmpIndex] = tmpIndex + uwOffset;
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	while(1)
	{
		HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
		HAL_Delay(500);
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
