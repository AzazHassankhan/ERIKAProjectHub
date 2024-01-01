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
    UART_1_PutString("******** MP3 Start********\r");
}

/*========================================
   Function to Show a message when the correct button is pressed
 *========================================
*/
void UART_SongPlay(const char8 *songplay)
{
    UART_1_PutString("Song Playing => ");
    UART_1_PutString(songplay);
    UART_1_PutString("\r");
}

/*============================================
   Function to Show a message when the wrong button is pressed
 *============================================
*/
void UART_SongPause()
{
    UART_1_PutString("Song Paused\r");
}

/* ===========================================
 * Function to Show Reaction timing on UART
 *============================================
 */
void UART_VolumeIncrease()
{
    UART_1_PutString("Volume Increase\r");
}

void UART_VolumeDecrease()
{
    UART_1_PutString("Volume Decrease\r");
}
void UART_SongStopped()
{
    UART_1_PutString("Song Stopped\r");
}

void UART_NextSong(const char8 *nextsong)
{
    UART_1_PutString("Next Song => ");
    UART_1_PutString(nextsong);
    UART_1_PutString("\r");
}
void UART_PrevSong(const char8 *Prevsong)
{
    UART_1_PutString("Previous Song => ");
    UART_1_PutString(Prevsong);
    UART_1_PutString("\r");
}
void UART_SongResume()
{
    UART_1_PutString("Resume Song\r");
}

void UART_SongData(int data)
{   
    char str[5];
    sprintf(str, "%d", data);
    UART_1_PutString(str);
    UART_1_PutString("\r");
}
