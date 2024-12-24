#include "key.h"
#include "cmsis_os2.h"


	
void key_init(void)
{
	/* enable GPIO  and EXTI 时钟 */
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_SYSCFG);
	
	gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);

	/* enable and set key EXTI interrupt priority */
	nvic_irq_enable(EXTI0_IRQn, 4U, 0U);
	/* connect key EXTI line to key GPIO pin */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);
    /* configure key EXTI line */
    exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_flag_clear(EXTI_0);
}

uint8_t key_scan(uint8_t mode)
{

	 static KeyState key_state = KEY_UP; // 当前按键状态，初始为抬起
    uint8_t key_value = 0;              // 按键事件标识，默认无事件
	
	if(mode)
    {
        key_state = KEY_UP; // 重置按键状态为抬起
    }

    if(key_state == KEY_UP && KEY1)
    {
        osDelay(3); // 消抖延时
        if(KEY1)
        {
            key_state = KEY_DOWN; // 按键按下
        }
    }

    if(key_state == KEY_DOWN && !KEY1)
    {
        osDelay(3); // 消抖延时
        if(!KEY1)
        {
            key_state = KEY_UP;   // 按键抬起
            key_value = 1;        // 按键按下并抬起事件
        }
    }

    return key_value;
}


//void key_scan(void)
//{
//    if(gpio_input_bit_get(GPIOA,GPIO_PIN_0) == SET) // 检测 WK_UP 按键按下
//    {
//        /* 延迟消抖 */
//        delay_1ms(20);
//        if(gpio_input_bit_get(GPIOA,GPIO_PIN_0) == SET) // 再次检测 WK_UP 按键按下
//        {
//            /* WK_UP 按键按下执行功能 */
//            gpio_bit_toggle(GPIOE,GPIO_PIN_3); // LED1 电平状态翻转
//            printf("key press!\r\n");
//            while(gpio_input_bit_get(GPIOA,GPIO_PIN_0) == SET); // 检测 WK_UP 按键松开
//            printf("key release!\r\n");
//        }
//    }
//}
