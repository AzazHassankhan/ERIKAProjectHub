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

void PWM_Start_Func()
{
	PWM_1_Start();
	PWM_2_Start();
	PWM_3_Start();
}

void PWM_Led_Fader_Func()
{
	for (uint8 i = 0; i < 255; i++)
	{
		PWM_1_WriteCompare(i);
		CyDelay(5);
	}

	for (uint8 i = 255; i > 0; i--)
	{
		PWM_1_WriteCompare(i);
		PWM_2_WriteCompare(255 - i);
		CyDelay(5);
	}

	for (uint8 i = 255; i > 0; i--)
	{
		PWM_2_WriteCompare(i);
		PWM_3_WriteCompare(255 - i);
		CyDelay(5);
	}

	for (uint8 i = 255; i > 0; i--)
	{
		PWM_3_WriteCompare(i);
		CyDelay(5);
	}
}
#include "project.h"

// Define a structure to hold RGB values and time
typedef struct
{
	int red;
	int green;
	int blue;
	int timeInMS;
}RG_Glow_t;

// Function to handle LED glowing based on predefined configurations
void GlowerFunc()
{
	// Predefined array of RGB configurations with respective time intervals
	const RG_Glow_t RG_glowtable_1[] = {
		{ 255, 0, 0, 500 },
		{ 0, 255, 0, 500 },
		{ 0, 0, 255, 500 },
		{ 0, 0, 0, 100 },
		{ 255, 255, 255, 100 },
		{ 0, 0, 0, 100 },
		{ 255, 255, 255, 100 },
		{ 0, 0, 0, 100 },
		{ 255, 255, 255, 100 }
	};

	// Calculate the number of elements in the array
	int numElements = sizeof(RG_glowtable_1) / sizeof(RG_glowtable_1[0]);

	// Loop through each configuration in the array
	for (int i = 0; i < numElements; ++i)
	{
		// Set LED colors based on the current configuration
		RGB_red_Write(RG_glowtable_1[i].red);
		RGB_green_Write(RG_glowtable_1[i].green);
		RGB_blue_Write(RG_glowtable_1[i].blue);

		// Delay for the specified time
		CyDelay(RG_glowtable_1[i].timeInMS);
	}
}
/*[] END OF FILE */