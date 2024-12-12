#include "gd32f4xx.h"                   // Device header


#define COMn                          2U
#define COM0                        USART0
#define COM0_GPIO_CLK               RCU_GPIOA

#define COM0_GPIO_PORT              GPIOA
#define COM0_AF                     GPIO_AF_7


#define COM0_TX_PIN                 GPIO_PIN_9
#define COM0_RX_PIN                 GPIO_PIN_10

#define COM1_TX_PIN                 GPIO_PIN_2
#define COM1_RX_PIN                 GPIO_PIN_3
void gd_uart_init(uint32_t com);

