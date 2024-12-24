#include "usart.h"
#include "stdio.h"

#define USART_COUNT 2
static rcu_periph_enum COM_CLK[COMn] = {RCU_USART0, RCU_USART1};
static uint32_t COM_TX_PIN[COMn] = {COM0_TX_PIN, COM1_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {COM0_RX_PIN, COM1_RX_PIN};
static uint32_t usart_list[] = {USART0, USART1}; 

/*!
    \brief     find com index
    \param[in]  com   串口号 
	\param[in]  size   
    \param[out] none
    \retval     none
*/
int find_com_id(uint32_t com,  int size) {
    for (int i = 0; i < size; i++) {
        if (usart_list[i] == com) {
            return i; // 找到匹配的 USART 后返回索引
        }
    }
    return -1; // 未找到匹配的 USART
}

/*!
    \brief    configure usart
    \param[in]  com   串口号    
    \param[out] none
    \retval     none
*/
void gd_uart_init(uint32_t com)
{
	uint32_t COM_ID = 0;
	int8_t err_code= find_com_id(com,  USART_COUNT);
	if(err_code == -1)
	{
		return;
	}
	/* enable GPIO and USARTclock */
    rcu_periph_clock_enable(COM0_GPIO_CLK);
    rcu_periph_clock_enable(COM_CLK[COM_ID]);

    /* connect port to USARTx_Tx and USARTx_Rx */
    gpio_af_set(COM0_GPIO_PORT, COM0_AF, COM_TX_PIN[COM_ID] | COM_RX_PIN[COM_ID]);
    /* configure USART Tx and USART Rx as alternate function push-pull */
    gpio_mode_set(COM0_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_TX_PIN[COM_ID]| COM_RX_PIN[COM_ID]);
    gpio_output_options_set(COM0_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, COM_TX_PIN[COM_ID]|COM_RX_PIN[COM_ID]);

    /* USART configure */
	usart_deinit(com);
	usart_baudrate_set(com, 115200);	
	usart_word_length_set(com, USART_WL_8BIT);
	usart_stop_bit_set(com, USART_STB_1BIT);
	usart_parity_config(com, USART_PM_NONE);	
	usart_hardware_flow_rts_config(com, USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(com, USART_CTS_DISABLE);
	usart_receive_config(com, USART_RECEIVE_ENABLE);
	usart_transmit_config(com, USART_TRANSMIT_ENABLE);
}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART1, (uint8_t)ch);
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    return ch;
}
