#include "gpio.h"

void gd_gpio_init(void)
{
	// LED1 
	rcu_periph_clock_enable(RCU_GPIOE);
	/* configure LED1 port */
	gpio_mode_set(LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_PIN);
	gpio_output_options_set(LED1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED1_PIN);
	/* turn off LED1 */
	gpio_bit_set(LED1_PORT, LED1_PIN);
	
	// LED2
	rcu_periph_clock_enable(RCU_GPIOD);
	gpio_mode_set(LED2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_PIN);
	gpio_output_options_set(LED2_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED2_PIN);
	gpio_bit_set(LED2_PORT, LED2_PIN);
	
	// LED3
	rcu_periph_clock_enable(RCU_GPIOG);
	gpio_mode_set(LED3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED3_PIN);
	gpio_output_options_set(LED3_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED3_PIN);
	gpio_bit_set(LED3_PORT, LED3_PIN);
	
	// LED4 引脚复用为 TIMER1_CH0
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(LED4_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED4_PIN);
	gpio_output_options_set(LED4_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED4_PIN);
	/* TIMER1_CH0 */
	gpio_af_set(LED4_PORT, GPIO_AF_1, LED4_PIN);
}
