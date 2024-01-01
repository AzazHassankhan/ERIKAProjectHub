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
#include "valerie.h"
#include "CastleOfGlass.h"
#include "Boxer.h"
#include "project.h"
// Define a structure to hold song data
struct Song_Data
{
	char *title;
    int  size;
	uint8_t *data;
};

typedef struct Song_Data Playlist;

Playlist Playlist_Obj[] = {
    { "Valerie - Amy Whinehouse", sizeof(SONG_Valerie), (uint8_t*)&SONG_Valerie },
    { "Boxer - Simon & Garfunkel", sizeof(SONG_Boxer), (uint8_t*)&SONG_Boxer},
    { "Castle of Glass - Linkin Park", sizeof(SONG_Castle), (uint8_t*)&SONG_Castle }
};
    
/* [] END OF FILE */
