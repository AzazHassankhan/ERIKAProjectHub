/**
 * @file
 * @brief Brief description of the file or module.
 *
 * Detailed description of the file or module.
 */
#include "project.h"
/**
 * @brief Initializes UART communication.
 * 
 * Detailed description of the UART initialization function.
 */
void UART_init();

/**
 * @brief Plays the current song over UART.
 * 
 * Detailed description of the function to play a song.
 */
void UART_SongPlay();

/**
 * @brief Pauses the currently playing song over UART.
 * 
 * Detailed description of the function to pause a song.
 */
void UART_SongPause();

/**
 * @brief Increases the volume of the song being played over UART.
 * 
 * Detailed description of the function to increase volume.
 */
void UART_VolumeIncrease();

/**
 * @brief Decreases the volume of the song being played over UART.
 * 
 * Detailed description of the function to decrease volume.
 */
void UART_VolumeDecrease();

/**
 * @brief Indicates that the song playback has stopped over UART.
 * 
 * Detailed description of the function to handle stopped song.
 */
void UART_SongStopped();

/**
 * @brief Plays the next song over UART.
 * 
 * Detailed description of the function to play the next song.
 */
void UART_NextSong(const char8 *nextsong);

/**
 * @brief Plays the previous song over UART.
 * 
 * Detailed description of the function to play the previous song.
 */
void UART_PrevSong(const char8 *Prevsong);

/**
 * @brief Resumes the paused song over UART.
 * 
 * Detailed description of the function to resume a paused song.
 */
void UART_SongResume();

/**
 * @brief to Show song data on uart.
 * 
 * Detailed description of showing data on uart.
 */
void UART_SongData(int data);


