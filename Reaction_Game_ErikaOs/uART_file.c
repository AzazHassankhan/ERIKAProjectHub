/* ========================================
 *
 * COPYRIGHT [YOUR COMPANY], [THE YEAR]
 * ALL RIGHTS RESERVED.
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF YOUR COMPANY.
 *
 *=========================================
 */

#include "project.h"
#include "stdio.h"

/*========================================
       Function to initialize UART and show the initial message
 *========================================
*/
void UART_init()
{
    UART_1_Start();
    UART_1_PutString("******** Reaction test program ********\r");
    UART_1_PutString("Press one of the two buttons to start...\r");
}

/*========================================
   Function to Show a message when the correct button is pressed
 *========================================
*/
void UART_correct()
{
    UART_1_PutString("Great - correct button pressed\r");
}

/*============================================
   Function to Show a message when the wrong button is pressed
 *============================================
*/
void UART_wrong()
{
    UART_1_PutString("Bad - Wrong button pressed\r");
}

/* ===========================================
 * Function to Show Reaction timing on UART
 *============================================
 */
void UART_time_reaction(int counter)
{
    char str[5];
    sprintf(str, "%d", counter);
    UART_1_PutString(str);
    UART_1_PutString("ms \r");
}

/* =============================================
 * Function to Show Final Score message on UART
 * Total Reaction Time message on UART
 *==============================================
 */
void UART_final(int correct, int Total_time)
{
    char str[5];
    // correct buttons pressed
    sprintf(str, "%1d", correct);
    UART_1_PutString("-----------*************---------\r");
    UART_1_PutString("Total Correct score = ");
    UART_1_PutString(str);
    // total reaction time
    sprintf(str, "%1d", Total_time);
    UART_1_PutString("\rTotal Reaction Time = ");
    UART_1_PutString(str);
    UART_1_PutString("ms \r");
    // average reaction time
    sprintf(str, "%1d", Total_time/10);
    UART_1_PutString("\rAverage Reaction Time = ");
    UART_1_PutString(str);
    UART_1_PutString("ms \r");
}

/*=============================================
 * Function to display a message when the reaction is too slow
 *==============================================
 */
void UART_Slow()
{
    UART_1_PutString("Too Slow\r");
}
