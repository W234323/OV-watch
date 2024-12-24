#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

#define KEY1_PORT	GPIOA
#define KEY1_PIN	GPIO_PIN_0
#define KEY1		gpio_input_bit_get(KEY1_PORT, KEY1_PIN)

// 定义状态
    typedef enum {
        KEY_UP = 1,
        KEY_DOWN = 0
    } KeyState;
	
void key_init(void);
uint8_t key_scan(uint8_t mode);

#endif
