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
#include "project.h"       /* Include project-specific definitions */
#include "global.h"        /* Include global definitions and variables */
#include "derivate.h"      /* Include derivate-specific definitions */
#include "tsk_control.h"   /* Include task control functions */
#include "tsk_io.h"        /* Include IO task functions */
#include "WatchDog.h"      /* Include watchdog timer functions */


/* To check the reset cause if the reset is because of watchdog timer or its a normal reset.*/
void Reset_Cause();

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
TASK(task_init)
{
    /* Start the UART */
    UART_Start();

    /* Start the PWM engine */
    PWM_Engine_Start();

    /* Start the ADC */
    ADC_Start();

    /* Start the watchdog timer */
    WD_Start(WDT_2048_3072_MS);

    /* This line MUST be called after the hardware driver
       initialization! */
    EE_system_init();

    /* Must be started after interrupt reconfiguration */
    EE_systick_start();

    /* Check the cause of the system reset */
    Reset_Cause();

    /* Set a relative alarm for 1 ms */
    SetRelAlarm(Alarm_1ms, 1, 1);

    /* Activate the control task */
    ActivateTask(tsk_control);

    /* Activate the background task */
    ActivateTask(tsk_background);

    /* Terminate the initialization task */
    TerminateTask();
}

/* Task for background activities */
TASK(tsk_background)
{
    /* Infinite loop */
    while (1)
    {    
        /* Check if all watchdog bits are set */
        if (WD_AllBits_Set())
        {         
            /* Trigger the watchdog timer */
            WD_Trigger();

            /* Clear all watchdog bits */
            WD_AllBits_Clear();
        }
    }
}

/* Define the ISR for power reset */
ISR1(Power_reset)
{
    /* Check if power reset button is pressed */
    if (PR_Button_Read())
        /* Perform a software reset */
        CySoftwareReset();
        
    /* Check if OS shutdown button is pressed */
    if (OS_Button_Read())
        /* Shutdown the OS with the E_OK status */
        ShutdownOS(E_OK);        
}

/* Function to check the reset cause */
void Reset_Cause()
{
    /* Check if the reset was caused by the watchdog */
    if (WD_CheckResetBit())
        /* Log message for watchdog reset */
        UART_PutString("---------Watchdog Reset--------- \r");
    else
        /* Log message for power reset */
        UART_PutString("---------Power reset--------- \r");
}

/* END OF FILE */