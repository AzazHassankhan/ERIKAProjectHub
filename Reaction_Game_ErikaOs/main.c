/*========================================
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
#include "game_file.h"
#include "faderFile.h"
#include "Glower.h"
// ISR Function for ticker++
ISR(systick_handler)
{
	CounterTick(cnt_systick);
}
//ISR function for category 2 interrupt 
// it calls event 
ISR2(isr_2)
{
	SetEvent(Game, button);
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
	Game_Init();
	PWM_Start_Func();

	//This line MUST be called after the hardware driver
	//initialization!
	EE_system_init();
	// Must be started after interrupt reconfiguration
	EE_systick_start();
	SetRelAlarm(Alarm_1, 100, 100);
	SetRelAlarm(Alarm_2, 101, 100);
	ActivateTask(Game);

	TerminateTask();

}

//Task for Reaction Game
TASK(Game)
{
	Game_Play();

}
//Task for random time generator
TASK(tsk_sleep)
{
	SetEvent(Game, sleepTask);

}
//Task for led Fader
TASK(tsk_fader)
{
	PWM_Led_Fader_Func();
	TerminateTask();
}

//Task for led glow
TASK(tsk_glower)
{
	Glower_Func();
	TerminateTask();
}

/*[] END OF FILE */