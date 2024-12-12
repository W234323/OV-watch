/*!
    \file    main.c
    \brief   led spark with systick

    \version 2024-01-15, V3.2.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/


#include <stdio.h>
#include "main.h"
#include "gd32f4xx.h"

/* System */
#include "systick.h"


/* Driver*/
#include "usart.h"

/* Freertos */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


void vTaskLED(void *pvParameters)
{
    (void) pvParameters;

    while(1)
    {
        printf("USART1 Init Success\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


int main(void)
{
	systick_config();
    gd_uart_init(USART1);
	
    xTaskCreate(vTaskLED, "LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // 启动调度器
    vTaskStartScheduler();

	
    while(1) {
		
    }
	
	
}



/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART1, (uint8_t)ch);
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    return ch;
}


