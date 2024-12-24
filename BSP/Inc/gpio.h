#ifndef __GPIO_H__
#define __GPIO_H__

#include "main.h"

// LED1 坏
#define LED1_PORT	GPIOE
#define LED1_PIN	GPIO_PIN_3

#define LED2_PORT	GPIOD
#define LED2_PIN	GPIO_PIN_7

#define LED3_PORT	GPIOG
#define LED3_PIN	GPIO_PIN_3

#define LED4_PORT	GPIOA
#define LED4_PIN	GPIO_PIN_5

void gd_gpio_init(void);

#endif
