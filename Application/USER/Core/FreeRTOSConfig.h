/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
/* 确保 stdint 只被编译器使用，而不是汇编器使用。 */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

// FreeRTOS 配置选项
#define configUSE_PREEMPTION           					 1   // 使用抢占式调度
#define configUSE_IDLE_HOOK             0   // 不使用空闲钩子函数
#define configUSE_TICK_HOOK             0   // 不使用滴答钩子函数
#define configCPU_CLOCK_HZ              ( SystemCoreClock )  // 设置 CPU 时钟频率,这里可以根据数据手册写死，也可以像我一样用内核文件定义
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )  // 滴答频率设置为 1000Hz,这个官方示例给的
#define configMAX_PRIORITIES            ( 5 )  // 最大优先级数目,根据需要修改
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 130 )  // 最小任务堆栈大小,根据需要修改,每个代表4个字节,即:130*4=520个字节
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 8 * 1024 ) )  // 堆大小设置为 8KB，,根据需要修改
#define configMAX_TASK_NAME_LEN         ( 16 )  // 任务名字的最大长度
#define configUSE_TRACE_FACILITY        1   // 启用追踪功能
#define configUSE_16_BIT_TICKS          0   // 使用 16 位的滴答计数器或者32位的滴答计时器
#define configIDLE_SHOULD_YIELD         1   // 空闲任务是否应该放弃 CPU,这里必须设置1
#define configUSE_MUTEXES               1   // 启用互斥量
#define configQUEUE_REGISTRY_SIZE       8   // 队列注册表的大小
#define configCHECK_FOR_STACK_OVERFLOW  0   // 不启用堆栈溢出检查
#define configUSE_RECURSIVE_MUTEXES     1   // 启用递归互斥量
#define configUSE_MALLOC_FAILED_HOOK    0   // 不使用内存分配失败钩子函数
#define configUSE_APPLICATION_TASK_TAG  0   // 不使用任务标签
#define configUSE_COUNTING_SEMAPHORES   1   // 启用计数信号量
#define configGENERATE_RUN_TIME_STATS   0   // 不生成运行时统计信息

/* 协程定义 */
#define configUSE_CO_ROUTINES           0   // 不使用协程
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )  // 最大协程优先级数

/* 软件定时器定义 */
#define configUSE_TIMERS                1   // 启用软件定时器
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1 )  // 定时器任务的优先级
#define configTIMER_QUEUE_LENGTH        5   // 定时器队列长度
#define configTIMER_TASK_STACK_DEPTH    ( configMINIMAL_STACK_SIZE * 2 )  // 定时器任务堆栈深度

/* 包含 API 函数的设置,根据自己需求启用 */
#define INCLUDE_vTaskPrioritySet      				  1   // 启用 vTaskPrioritySet 函数
#define INCLUDE_uxTaskPriorityGet     				  1   // 启用 uxTaskPriorityGet 函数
#define INCLUDE_vTaskDelete           				  1   // 启用 vTaskDelete 函数
#define INCLUDE_vTaskCleanUpResources 				  1   // 启用 vTaskCleanUpResources 函数
#define INCLUDE_vTaskSuspend        				  1   // 启用 vTaskSuspend 函数
#define INCLUDE_vTaskDelayUntil       				  1   // 启用 vTaskDelayUntil 函数
#define INCLUDE_vTaskDelay             				  1   // 启用 vTaskDelay 函数
#define INCLUDE_xTaskGetSchedulerState         		  0
#define INCLUDE_xTaskGetCurrentTaskHandle       	  1
#define INCLUDE_uxTaskGetStackHighWaterMark           0
#define INCLUDE_uxTaskGetStackHighWaterMark2    	  0
#define INCLUDE_xTaskGetIdleTaskHandle          	  0
#define INCLUDE_eTaskGetState                  		  0
#define INCLUDE_xEventGroupSetBitFromISR        	  0
#define INCLUDE_xTimerPendFunctionCall        		  0
#define INCLUDE_xTaskAbortDelay              	      0
#define INCLUDE_xTaskGetHandle                		  0
#define INCLUDE_xTaskResumeFromISR            		  0

/* Cortex-M 特定定义 */
#ifdef __NVIC_PRIO_BITS
    /* 当使用 CMSIS 时，__NVIC_PRIO_BITS 会被指定 */
    #define configPRIO_BITS           __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS           4   /* 15 个优先级 */
#endif

/* 可用于调用 "set priority" 函数的最低中断优先级 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0xf

/* 可由任何中断服务例程使用的最高中断优先级
（较高的优先级具有较低的数值）。不要从比这更高优先级
的中断中调用 FreeRTOS API 函数！*/
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* 内核端口层自身使用的中断优先级。适用于所有 Cortex-M 端口，
不依赖于任何特定的库函数 */
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY 不能设置为零 !!!!
参见 http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* 不依赖 assert.h 头文件提供的正常 assert() 语义 */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* 定义将 FreeRTOS 端口中断处理程序映射到它们的 CMSIS 标准名称 */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */


