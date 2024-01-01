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


static uint8 array[] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
		0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111
	};


/*========================================
   Funtion to show dot on both segments
 *======================================== */
void Song_segment(uint8 index)
{
	Sel_A_Write(1);
	Control_Reg_1_Write(array[index]);

}

/*========================================
   Funtion to show 1 or 2 randomly
   on both segments
 *======================================== */
void  Volume_segment(int *index)
{   
    if (*index<10 && *index>=0)
{   Sel_A_Write(0);
    Control_Reg_1_Write(array[*index]);}
	else if(*index>9)
    {*index=9;}
    else if(*index<0)
    {*index=0;}
	
}

/*[] END OF FILE */