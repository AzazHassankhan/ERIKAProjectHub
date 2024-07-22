/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"                 /* Include project-specific definitions */
#include "global.h"                  /* Include global definitions and variables */
#include "derivate.h"                /* Include derivate-specific definitions */
#include "tsk_hmi.h"                 /* Include task control functions */
#include "tsk_io.h"                  /* Include IO task functions */
#include "tsk_clock_control.h"       /* Include task control functions */
#include "tft.h"

/* ISR Function for ticker++ */
ISR(systick_handler)
{
    /* Increment the application counter */
    CounterTick(cnt_systick);
}

/* Main function */
int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable;

    /* Set systick period to 1 ms. */
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));

    /* Enable systick interrupt */
    EE_systick_enable_int();

    /* Start Operating System */
    for (;;)
        /* Start the operating system with the default application mode */
        StartOS(OSDEFAULTAPPMODE);
}

/* Task for Initialization and activation of components */
TASK(tsk_init)
{
    // Start UART for logging
    UART_LOG_Start();

    // Initialize TFT display
    TFT_init();

    // Set TFT backlight intensity
    TFT_setBacklight(100);

    // Initialize system-specific functionality
    EE_system_init();
    
    // Initialize system-specific functionality
	EE_systick_start();
    
    TFT_setTextSize(3);
    
    /* Set a relative alarm for 1 ms */
    SetRelAlarm(Alarm_IO, 1, 1);
    
    SetRelAlarm(Alarm_HMI, 1, 1);
    
    /* Activate the background task */
    ActivateTask(tsk_background);

    /* Activate the HMI task */
    //ActivateTask(tsk_HMI);
    
    /* Activate the Clock Control task */
    ActivateTask(tsk_Clock_Control);
    
    /* Terminate the initialization task */
    TerminateTask();
}

/* Task for background activities */
TASK(tsk_background)
{
    /* Infinite loop */
    while (1)
    {}
}

/* [] END OF FILE */