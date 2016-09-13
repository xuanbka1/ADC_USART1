#ifndef __ADC_H
#define __ADC_H
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

//++++++++++++++++++++++++++++  ADC1   ++++++++++++++++++++++++++++
//#define ADC1_DR_ADDR    ((u32)0x4001244C)
#define ADC1_DR_ADDR    ((u32)(ADC1_BASE+0x4C))
#define ADC2_DR_ADDR	((u32)(ADC2_BASE+0x4C))
#define ADC3_DR_ADDR	((u32)(ADC3_BASE+0x4C))
/********************************************************/
void ADC1_Configuration(void);
void ADC2_Configuration(void);
void ADC3_Configuration(void);
uint16_t read_adc(ADC_TypeDef* ADCx,u8 ADC_Channel);
#endif
