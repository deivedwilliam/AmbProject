/*
 * ADV7513.c
 *
 *  Created on: 14 de ago de 2020
 *      Author: Deived
 */


#include "ADV7513.h"
#include "main.h"
#include "stdio.h"


#define ADV7513_I2C_DELAY 5000


extern I2C_HandleTypeDef hi2c1;
extern ADV7513ConfigTypeDef AdvConfigStruct;

static void HDMI_IO_Write(uint8_t deviceAddress, uint8_t reg, uint8_t value)
{
	while(HAL_I2C_Mem_Write(&hi2c1,
			deviceAddress,
			reg,
			sizeof(uint8_t),
			&value,
			sizeof(uint8_t),
			ADV7513_I2C_DELAY) != HAL_OK);
}

static uint8_t HDMI_IO_Read(uint8_t deviceAddress, uint8_t reg)
{
	uint8_t tmp = 0;

	while(HAL_I2C_Mem_Read(&hi2c1,
			deviceAddress,
			reg,
			I2C_MEMADD_SIZE_8BIT,
			&tmp,
			1,
			ADV7513_I2C_DELAY) != HAL_OK);

	return tmp;
}

static void ADV7513_ClearBufferCEC(void)
{
	uint8_t tmp;

	//Set high for clear cec buffer
	tmp = HDMI_IO_Read(ADV7513_I2C_CEC_ADDRESS, 0x4A);
	tmp |= 0x07;
	HDMI_IO_Write(ADV7513_I2C_CEC_ADDRESS, 0x4A, tmp);

	//set again low
	tmp = HDMI_IO_Read(ADV7513_I2C_CEC_ADDRESS, 0x4A);
	tmp &= 0xF8;
	HDMI_IO_Write(ADV7513_I2C_CEC_ADDRESS, 0x4A, tmp);
}

uint8_t ADV7513_Init(void)
{
	HAL_GPIO_WritePin(PD_GPIO_Port, PD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PD_GPIO_Port, PD_Pin, GPIO_PIN_RESET);
	ADV7513_Configure(&AdvConfigStruct);

	return 0;
}
/**
  * @brief  Power on the ADV7513 bridge.
  * @param  None
  * @retval None
  */

void ADV7513_PowerOn(void)
{
//	uint8_t tmp = 0;
//
//	HAL_I2C_Mem_Read(&hi2c1,
//			DeviceAddress,
//			0x41,
//			sizeof(uint8_t),
//			&tmp,
//			sizeof(uint8_t),
//			ADV7513_I2C_DELAY);
//
//
//	tmp &= ~0x40;
//
//	HAL_I2C_Mem_Write(&hi2c1,
//			DeviceAddress,
//			0x41, sizeof(uint8_t),
//			&tmp, sizeof(uint8_t),
//			ADV7513_I2C_DELAY);

}

/**
  * @brief  Power off the ADV7513 bridge.
  * @param  None
  * @retval None
  */

void ADV7513_PowerDown(void)
{
//	uint8_t tmp = 0;
//
//	HAL_I2C_Mem_Read(&hi2c1,
//			DeviceAddress,
//			0x41,
//			sizeof(uint8_t),
//			&tmp,
//			sizeof(uint8_t),
//			ADV7513_I2C_DELAY);
//
//
//	tmp |= 0x40;
//
//	HAL_I2C_Mem_Write(&hi2c1,
//			DeviceAddress,
//			0x41, sizeof(uint8_t),
//			&tmp, sizeof(uint8_t),
//			ADV7513_I2C_DELAY);
}


uint8_t ADV7513_ReadDeviceVersion(void)
{
	uint8_t tmp = 0;

	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x00);

	return tmp;
}

void ADV7513_Configure(ADV7513ConfigTypeDef * config)
{
	uint8_t tmp = 0;
	uint8_t buffer[16];
	uint16_t deviceAddress = 0;



	/*Power up the tx*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x41);
//	tmp &= ~0x40;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x41, tmp);
//
////	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xD6);
////	tmp |= 0xc0;
////	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xD6, tmp);
//
//
//	/*Fixed registers that must be set on power up*/
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x98, 0x03);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9A);
//	tmp |= 0xE0;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9A, tmp);
//
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9C, 0x30);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9D);
//	tmp |= 0b01;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9D, tmp);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xA2, 0xA4);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xA3, 0xA4);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xE0, 0xD0);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xF9, 0x00);
//	/* end configuration fixed registers*/
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_CEC_ADDRESS, 0x4E);
//	tmp |= 0x7F;
//	HDMI_IO_Write(ADV7513_I2C_CEC_ADDRESS, 0x4E, tmp);
//	/*Set up video input mode*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x15);
//	tmp &= 0xf0;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x15, tmp);
//
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x16);
//	tmp |= 0x30;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x16, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17);
//	tmp |= 0x60;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x48);
//	tmp |= 0x08;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x48, tmp);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x02, 0x1a);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x03, 0xd0);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x08, 0x6d);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x09, 0xdd);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A);
//	tmp |= 0x80;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x44);
//	tmp |= 0x10;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x44, tmp);
//
//	//aspect ratio
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17);
//	tmp &= 0xFC;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17, tmp);
//	/*end configuration video input*/
//
//	/*enable sync*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x41);
//	tmp |= 0x02;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x41, tmp);
//
//	/*Set up video output mode*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x16);
//	tmp |= 0x30;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x16, tmp);
//
//	/*HDCP enable*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAF);
//	tmp |= 0x80;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAF, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAF);
//	tmp |= 0x02;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAF, tmp);
//
//	//tx,rx interrupt enable
//	//tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x95);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x95, 0xFF);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x94);
//	tmp |= 0xc0;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x94, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x95);
//	tmp |= 0x40;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x95, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x94);
//	tmp |= 0x02;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x94, tmp);
//	HAL_Delay(10);
////	do
////	{
//		tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x97);
//		HAL_Delay(100);
//	//	printf("%u\n", tmp);
//	//}while(((tmp >> 6) & 0x01) != 1);
//	tmp |= 0x40;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x97, tmp);
//
//	/*end hdcp register*/
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x40);
//	tmp |= 0b10000000;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x40, tmp);
//
//	/*Audio Setup*/
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x01, 0x00);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x02, 0x18);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x03, 0x00);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A);
//	tmp &= 0x8F;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A, tmp);
//	/* end audio setup*/
//
//	/*Audio mode*/
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0B);
//	tmp &= 0x7F;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0B, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0C);
//	tmp &= 0x04;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0C, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x15);
//	tmp |= 0x20;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x15, tmp);
//
//	//word length
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x14);
//	tmp |= 0x0B;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x14, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A);
//	tmp &= 0x8F;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x0A, tmp);
//	/* end audio mode*/
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x3C, 0x01);
//
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDE, 0x18);
//
//	/*hsync front*/
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd7, 0x04);
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd8);
//	tmp &= 0x3F;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd8, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd9);
//	tmp &= 0x0F;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd9, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd8);
//	tmp |= 0x06;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd8, tmp);
//
//	/*vsync front*/
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd9);
//	tmp &= 0xF0;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xd9, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDA);
//	tmp |= 0x2C;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDA, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDB);
//	tmp |= 0x02;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDB, tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDA);
//	tmp &= 0xFC;
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDA, tmp);
//
////	/*avi setup*/
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x44, 0xF9);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x4A, 0xF0);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x55, 0x1A);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x56, 0x98);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x57, 0xCB);
//	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x73, 0x07);
//
//
//
//
//
//
//	//enable sync adjust
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x3D);
//
//	printf("0x3D = %u\n", tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x3E);
//
//	printf("0x3E = %u\n", tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x96);
//
//	printf("0x96 = %u\n", tmp);
//
//	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x42);
//
//	printf("0x42 = %u\n", tmp);

	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x98, 0x03);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x01, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x02, 0x18);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x03, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x14, 0x70);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x15, 0x20);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x16, 0x30);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x18, 0x46);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x40, 0x80);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x41, 0x10);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x49, 0xA8);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x55, 0x10);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x56, 0x08);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x96, 0xF6);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x73, 0x07);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x76, 0x1F);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x98, 0x03);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x99, 0x02);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9A, 0xE0);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9C, 0x30);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x9D, 0x61);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xA2, 0xA4);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xA3, 0xA4);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xA5, 0x04);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAB, 0x40);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xAF, 0x16);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xBA, 0x60);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xD1, 0xFF);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xDE, 0x10);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xE4, 0x60);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0xFA, 0x7D);
		tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17);
		tmp &= 0xFC;
		HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x17, tmp);
			tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0x48);
			tmp |= 0x08;
			HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS0, 0x48, tmp);
}

uint16_t ADV7513_GetDeviceID(void)
{
	uint16_t tmp = 0;

	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xF5) << 8;
	tmp |= HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS0, 0xF6);

	return tmp;
}
