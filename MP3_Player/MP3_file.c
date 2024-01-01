/*========================================
 *@game_file.c
 *@brief Your file brief description here
 *========================================*/

// Including necessary header files
#include "project.h"
#include "stdlib.h"
#include "uART_file.h"
#include "MP3_file.h"
#include "segment_file.h"
#include "Song_Records.h"

/*========================================
               Defining states
 *========================================
*/

// Define a state enumeration for the MP3
typedef enum
{
	Is_Standby,	// State: Song Standby mode
	Is_Playing,	// State: Song Playing mode
    Is_Paused,  // State: Song Paused mode
}MP3_state_t;

// Define a structure to hold MP3 state
typedef struct
{
	MP3_state_t state;	// State variable
	int volume;
	uint8 Song_time;
	uint8 Song_state;
	int Current_Song;
	uint8 SongTerminate;
    int Total_songs;
}

MP3_state;

/*========================================
Creating game object to control state
 *========================================
*/

static MP3_state MP3_obj = { Is_Standby, 0, 0, 0, -1, 0, 0};

/*========================================
         Run &Initialize Mp3
 *========================================
*/

void MP3_Init()
{
	UART_init();	// Initialize UART
    MP3_obj.Total_songs = 1;
    Volume_segment(&MP3_obj.volume);
    
}

/*========================================
 Function to record and show song timing on segment 
 *========================================
*/

/*========================================
             State Machine 
 *========================================
*/

// Function to handle game state machine
void MP3_Play()
{
	uint8 exit_loop = 0;
	EventMaskType ev = 0;	// Event variable

	// Main loop for the state machine
	while (!exit_loop)
	{
		// State machine switch-case
		switch (MP3_obj.state)
		{
			case Is_Standby:
				WaitEvent(button_1 | button_2 | button_3);
				GetEvent(task_MP3, &ev);
				ClearEvent(ev);
				if (ev & button_1)	//select next song {}

				{

					Next_Song();
				}

				if (ev & button_2)	//select previous song {}

				{

					Prev_Song();
				}

				if (ev & button_3)	//start to play the selected song
				{
					Song_Play();
					MP3_obj.state = Is_Playing;
				}

				break;

			case Is_Playing:
				WaitEvent(ev_1s | button_1 | button_2 | button_3 | button_4);
				GetEvent(task_MP3, &ev);
				ClearEvent(ev);
				if (ev & button_1)	// increase volume
				{
					Volume_Increase();
				}

				if (ev & button_2)	// decrease volume
				{
					Volume_Decrease();
				}

				if (ev & button_3)	// pause and resume the song (press again to resume)
				{
					Song_PauseAndResume();
                    MP3_obj.state = Is_Paused;
                    CyDelay(200);
				}

				if (ev & button_4)	// stop the song and go back to standby mode
				{
					Song_Stopped();
					MP3_obj.state = Is_Standby;
				}

				if (ev &ev_1s && MP3_obj.Song_time > 9)	// when song time is over play next song
				{
					Automatic_Nextsong();
				}

				break;
                
            case Is_Paused:
                    
                	if (Button_3_Read())	// pause and resume the song (press again to resume)
				{
					Song_PauseAndResume();
                    MP3_obj.state = Is_Playing;
                  
                    ClearEvent(ev);
				}
                
                if (Button_4_Read())	// stop the song and go back to standby mode
				{
					Song_Stopped();
					MP3_obj.state = Is_Standby;
				}
                
                break;
    
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
/*========================================
             State Functions
 *========================================
*/
// Song Time calculation
void Song_play_time()
{
	if (MP3_obj.Song_time < 10) Song_segment(MP3_obj.Song_time);
	MP3_obj.Song_time++;

}

// Song Paused and Resume
void Song_PauseAndResume()
{
	MP3_obj.Song_state = ~MP3_obj.Song_state;
	if (MP3_obj.Song_state)
	{
		UART_SongPause();
		CancelAlarm(Alarm_1);
	}
	else
	{
		UART_SongResume();
		SetRelAlarm(Alarm_1, 1000, 1000);
	}
}

// Automatic next song play
void Automatic_Nextsong()
{
	MP3_obj.Song_time = 0;
	Next_Song();
	Song_Play();
}

// Song Stopped
void Song_Stopped()
{
	UART_SongStopped();
	MP3_obj.Song_state = 0;
	MP3_obj.SongTerminate = 1;
	Song_segment(MP3_obj.Song_time = 0);
	CancelAlarm(Alarm_1);
}

// increase volume
void Volume_Increase()
{
	MP3_obj.volume++;
	UART_VolumeIncrease();
	Volume_segment(&MP3_obj.volume);

}

// decrease volume
void Volume_Decrease()
{
	MP3_obj.volume--;
	UART_VolumeDecrease();
	Volume_segment(&MP3_obj.volume);

}

// select the next song in the playlist
void Next_Song()
{
	if (MP3_obj.Current_Song <= MP3_obj.Total_songs) MP3_obj.Current_Song++;
	else MP3_obj.Current_Song = 0;
    
	UART_NextSong(Playlist_Obj[MP3_obj.Current_Song].title);
}

// select the Previous song in the playlist
void Prev_Song()
{
	if (MP3_obj.Current_Song > -1 && MP3_obj.Current_Song != 0 ) MP3_obj.Current_Song--;
	else MP3_obj.Current_Song = 0;
	UART_NextSong(Playlist_Obj[MP3_obj.Current_Song].title);
}

// Song Play
void Song_Play()
{
	if (MP3_obj.Current_Song == -1) {MP3_obj.Current_Song=0;}
    SetRelAlarm(Alarm_3, 1, 0);
	UART_SongPlay(Playlist_Obj[MP3_obj.Current_Song].title);
	SetRelAlarm(Alarm_1, 1000, 1000);
}

void Song_Playing()
{
	for (int i = 0; i <= Playlist_Obj[MP3_obj.Current_Song].size; i++)
	{
		if (MP3_obj.SongTerminate)
		{
			MP3_obj.SongTerminate = 0;
			TerminateTask();
		}
        
		UART_SongData(Playlist_Obj[MP3_obj.Current_Song].data[i]);
        CyDelay(100);
	}
}

/*[] END OF FILE */