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
#include "project.h"

// Define a structure to hold RGB values and time
typedef struct
{
    int red;       /**< Red value */
    int green;     /**< Green value */
    int blue;      /**< Blue value */
    int timeInMS;  /**< Time in milliseconds */
} RG_Glow_t;


// Function to handle LED glowing based on predefined configurations
void Glower_Func()
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
/* [] END OF FILE */
