#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

void Error_Handler(void);

#define LCD_COLOR_BLUE          ((uint32_t) 0xFF0000FF)

/** @brief Green value in ARGB8888 format
 */
#define LCD_COLOR_GREEN         ((uint32_t) 0xFF00FF00)

/** @brief Red value in ARGB8888 format
 */
#define LCD_COLOR_RED           ((uint32_t) 0xFFFF0000)


/* Exported types ------------------------------------------------------------*/
typedef enum {PASSED = 0, FAILED = !PASSED} TestStatus_t;
/* Exported constants --------------------------------------------------------*/
#define SDRAM_BANK_ADDR                 ((uint32_t)0xC0000000)

/* #define SDRAM_MEMORY_WIDTH        FMC_SDRAM_MEM_BUS_WIDTH_8  */
#define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16
/* #define SDRAM_MEMORY_WIDTH        FMC_SDRAM_MEM_BUS_WIDTH_32 */

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define NRF24_CSN_Pin GPIO_PIN_2
#define NRF24_CSN_GPIO_Port GPIOE
#define NRF24_CE_Pin GPIO_PIN_3
#define NRF24_CE_GPIO_Port GPIOE
#define NRF24_IRQ_Pin GPIO_PIN_4
#define NRF24_IRQ_GPIO_Port GPIOE
#define SD_DETECT_Pin GPIO_PIN_12
#define SD_DETECT_GPIO_Port GPIOD
#define LED_STATUS_Pin GPIO_PIN_13
#define LED_STATUS_GPIO_Port GPIOD
#define PD_Pin GPIO_PIN_6
#define PD_GPIO_Port GPIOC
#define INT_HDMI_Pin GPIO_PIN_7
#define INT_HDMI_GPIO_Port GPIOC


#ifdef __cplusplus
}
#endif

#endif
