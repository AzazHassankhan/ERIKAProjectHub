/*=============================================================================
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *============================================================================
 */


/*=============================================================================
 * @brief Initialize MP3 components
 *
 * Initializes MP3 components for the system.
 *============================================================================
 */
void MP3_Init();

/*=============================================================================
 * @brief Handle song timing functionality
 *
 * Function to manage and update song timing information.
 *============================================================================
 */
void Song_play_time();


/*=============================================================================
 * @brief MP3 Player State Machine
 *
 * State machine function managing MP3 player functionalities.
 *============================================================================
 */
void MP3_Play();


/*=============================================================================
 * @brief Pause and resume song playback
 *
 * Function to pause and resume the song.
 *============================================================================
 */
void Song_PauseAndResume();


/*=============================================================================
 * @brief Stop the song playback
 *
 * Function to stop the currently playing song.
 *============================================================================
 */
void Song_Stopped();


/*=============================================================================
 * @brief Increase the volume
 *
 * Function to increase the volume of the MP3 player.
 *============================================================================
 */
void Volume_Increase();


/*=============================================================================
 * @brief Decrease the volume
 *
 * Function to decrease the volume of the MP3 player.
 *============================================================================
 */
void Volume_Decrease();

/*=============================================================================
 * @brief PLay the song
 *
 * Function to Play the selected song of the MP3 player.
 *============================================================================
 */
void Song_Play();

/*=============================================================================
 * @brief Play the song next song autumatically after the song time is over
 *
 * Function to Play the next song autumatically after the time is over.
 *============================================================================
 */
void Automatic_Nextsong();
/*[] END OF FILE */

/*=============================================================================
 * @brief Select the next Song
 *
 * Function to select the next song .
 *============================================================================
 */
void Next_Song();

/*=============================================================================
 * @brief Select the Prevvious Song
 *
 * Function to select the Previous song .
 *============================================================================
 */
void Prev_Song();

/*=============================================================================
 * @brief Starting playing song
 *
 * Function to start playing song data.
 *============================================================================
 */
void Song_Playing();
/*[] END OF FILE */