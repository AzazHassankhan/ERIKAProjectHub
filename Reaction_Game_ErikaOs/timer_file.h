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

/**
 * @file ReactionTimer.h
 * @brief Header file containing reaction timer functionality.
 */

#ifndef REACTION_TIMER_H
#define REACTION_TIMER_H

#include "project.h"

/**
 * @brief Global variable to hold reaction time in milliseconds.
 */
static int reaction_time, Total_time = 0,Average_time=0;

/**
 * @brief Timer Interrupt: Captures the reaction time of the user in ms.
 *
 * This function is an interrupt service routine that captures the reaction time of the user.
 */
CY_ISR(button1)
{
	int counter = Timer_1_ReadCapture();
	reaction_time = 65536 - counter;
	Total_time += reaction_time;
    Average_time+= reaction_time;
	Timer_1_ReadStatusRegister();
	Timer_1_Stop();
	Timer_1_WriteCounter(0x0000);
}

/**
 * @brief Function to capture reaction time and handle timer events.
 *
 * This function captures the reaction time of the user based on timer values.
 *
 * @return 1 if reaction time is greater than or equal to 1000ms, otherwise 0.
 */
int Slow()
{
	int counter = Timer_1_ReadCounter();
	reaction_time = 65536 - counter;
	if (reaction_time >= 1000)
	{
		Total_time += reaction_time;
		Timer_1_ReadStatusRegister();
		Timer_1_Stop();
		Timer_1_WriteCounter(0x0000);
		return 1;
	}
	else
	{
		Timer_1_ReadStatusRegister();
		return 0;
	}
}

#endif /* REACTION_TIMER_H */

/* [] END OF FILE */
