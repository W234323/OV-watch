#include <usart.h>

static rcu_periph_enum COM_CLK[COMn] = {RCU_USART0,RCU_USART1};
static uint32_t COM_TX_PIN[COMn] = {COM0_TX_PIN,COM1_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {COM0_RX_PIN,COM1_RX_PIN};
static uint32_t usart_list[] = {USART0, USART1}; 


void gd_uart_init(uint32_t com)
{
	uint32_t COM_ID = 0;

	for (int i = 0; i < 2; i++) {
		if (usart_list[i] == com) {
			COM_ID = i; // 将索引赋值给COM_ID
			break; // 找到匹配的USART后退出循环
		}
	}
    rcu_periph_clock_enable(COM0_GPIO_CLK);

    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[COM_ID]);

    /* connect port to USARTx_Tx */
    gpio_af_set(COM0_GPIO_PORT, COM0_AF, COM_TX_PIN[COM_ID]);

    /* connect port to USARTx_Rx */
    gpio_af_set(COM0_GPIO_PORT, COM0_AF, COM_RX_PIN[COM_ID]);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(COM0_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,COM_TX_PIN[COM_ID]);
    gpio_output_options_set(COM0_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,COM_TX_PIN[COM_ID]);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(COM0_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,COM_RX_PIN[COM_ID]);
    gpio_output_options_set(COM0_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,COM_RX_PIN[COM_ID]);

    /* USART configure */
    usart_deinit(com);
    usart_baudrate_set(com,115200U);
    usart_receive_config(com, USART_RECEIVE_ENABLE);
    usart_transmit_config(com, USART_TRANSMIT_ENABLE);
    usart_enable(com);
}
