#include "timer.h"
#include "gpio.h"

void gd_timer1_init(uint16_t prescaler, uint32_t period)
{
	timer_parameter_struct timer1_init_para;
	
	/* enable timer1 clock */
	rcu_periph_clock_enable(RCU_TIMER1);
	/* CK_TIMER1 = 4 x CK_APB2 = 4 x (CK_AHB / 4)  = 4 x 50MHz = 200MHz */
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	/* init timer1_init_para struct */
	timer_struct_para_init(&timer1_init_para);
	/* reset TIMER1 */
	timer_deinit(TIMER1);
	
    /* TIMER1 configuration */
    timer1_init_para.prescaler         = prescaler - 1;				// 预分频值
    timer1_init_para.alignedmode       = TIMER_COUNTER_EDGE;		// 边沿对齐模式
    timer1_init_para.counterdirection  = TIMER_COUNTER_UP;			// 向上计数
    timer1_init_para.period            = period - 1;				// 自动重装载值
    timer1_init_para.clockdivision     = TIMER_CKDIV_DIV1;			// 时钟不分频
    timer1_init_para.repetitioncounter = 0;							// 重复计数器为 0
	/* init TIMER1 */
	timer_init(TIMER1, &timer1_init_para);
	
	 /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);//使能自动重加载
	timer_interrupt_enable(TIMER1,TIMER_INT_UP);//使能溢出中断
	nvic_irq_enable(TIMER1_IRQn, 4, 0);
    /* TIMER1 enable */
    timer_enable(TIMER1);

}


//中断函数
void TIMER1_IRQHandler(void)
{
    if(SET == timer_interrupt_flag_get(TIMER1,TIMER_INT_UP)){
        gpio_bit_toggle(LED3_PORT, LED3_PIN);
		/* clear TIMER interrupt flag */
		timer_interrupt_flag_clear(TIMER1,TIMER_INT_UP);
    }      
}
