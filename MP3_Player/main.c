/* ========================================
 *
 *Copyright YOUR COMPANY, THE YEAR
 *All Rights Reserved
 *UNPUBLISHED, LICENSED SOFTWARE.
 *
 *CONFIDENTIAL AND PROPRIETARY INFORMATION
 *WHICH IS THE PROPERTY OF your company.
 *
 *========================================
 */
#include "project.h"
#include "MP3_file.h"



// ISR Function for ticker++
ISR(systick_handler)
{
	CounterTick(cnt_systick);
}

int main(void)
{
	/*Enable global interrupts. */
	CyGlobalIntEnable;
	//Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1,
		BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	// Start Operating System
	for (;;)
		StartOS(OSDEFAULTAPPMODE);

}

//Task for Intialization and activation of components
TASK(task_init)
{
	MP3_Init();
	//This line MUST be called after the hardware driver
	//initialization!
	EE_system_init();
	// Must be started after interrupt reconfiguration
	EE_systick_start();
    SetRelAlarm(Alarm_2, 1000, 1000);
	ActivateTask(task_MP3);

	TerminateTask();

}

TASK(task_MP3)
{
	MP3_Play();
	TerminateTask();

}

TASK(task_segment)
{
	Song_play_time();
    TerminateTask();
}

TASK(task_song)
{
	Song_Playing();
    TerminateTask();
}

ISR2(ISR_Buttons)
{
	if (Button_1_Read()) SetEvent(task_MP3, button_1);
	if (Button_2_Read()) SetEvent(task_MP3, button_2);
	if (Button_3_Read()) SetEvent(task_MP3, button_3);
	if (Button_4_Read()) SetEvent(task_MP3, button_4);

}

/*[] END OF FILE */