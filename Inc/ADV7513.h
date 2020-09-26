#ifndef ADV7513_H_
#define ADV7513_H_

#include "main.h"




/**
  * @brief  ADV7533 I2C Addresses 0x7A / 0x78
  */
#define ADV7513_I2C_CEC_ADDRESS        		((uint8_t)0x78)
#define ADV7513_I2C_MAINMAP_ADDRESS0		((uint8_t)0x72)
#define	ADV7513_I2C_MAINMAP_ADDRESS1		((uint8_t)0x7A)

#define ADV7513_I2C_EDID_ADDRESS			((uint8_t)0x7E)

/**
  * @brief  ADV7513 Aspect ratio
  */
#define ADV7513_ASPECT_RATIO_16_9        ((uint8_t)0x00)
#define ADV7513_ASPECT_RATIO_4_3         ((uint8_t)0x01)



/**
  * @brief  ADV7533 Aspect ratio
  */
#define ADV7513_MODE_HDMI                0x1
#define ADV7513_MODE_DVI                 0x0


/*Hot Plug Detect Register Map*/

#define HPD_Reg_BitState(reg_value)					(((unsigned char)(reg_value >> 6)) & 0x01)
#define HPD_Reg_MonitorSenseState(reg_value)		(((unsigned char)(reg_value >> 5)) & 0x01)
#define HPD_Reg_InterruptEnableW(value)				(((unsigned char)(value << 7)))
#define HPD_Reg_InterrutEnableR(reg_value)			(((unsigned char)(reg_value >> 7)) & 0x01)
#define HPD_Reg_InterruptEnableSenseW(value)  		(((unsigned char)(value << 6)))
#define HPD_Reg_InterruptEnableSenseR(reg_value)  	(((unsigned char)(reg_value >> 6)) & 0x01)



/** @addtogroup ADV7513_Exported_Types
  * @{
  */

typedef struct
{
	uint16_t      HACT;
	uint16_t      HSYNC;
	uint16_t      HBP;
	uint16_t      HFP;
	uint16_t      VACT;
	uint16_t      VSYNC;
	uint16_t      VBP;
	uint16_t      VFP;
	uint8_t       ASPECT_RATIO;
}ADV7513ConfigTypeDef;



uint8_t ADV7513_Init(void);
void ADV7513_PowerOn(void);
void ADV7513_PowerDown(void);
void ADV7513_Configure(ADV7513ConfigTypeDef* config);
void ADV7513_PatternEnable(void);
void ADV7513_PatternDisable(void);
void ADV7513_ConfigAddress(uint8_t address);
uint8_t ADV7513_ReadDeviceVersion(void);
uint16_t ADV7513_GetDeviceID(void);

#endif
