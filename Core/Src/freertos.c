#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "main.h"
#include "gpio.h"
#include "user_TasksInit.h"

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
	.name = "defaultTask",
	.stack_size = 128 * 4,
	.priority = (osPriority_t)osPriorityNormal
};

void StartDefaultTask(void *argument)
{
	while(1)
	{

		gpio_bit_toggle(LED2_PORT, LED2_PIN);
		osDelay(500);
	}
}

void FREERTOS_Init(void)
{
	User_Tasks_Init();
	
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
}
