/*========================================
 * @segment_file.h
 * @brief Header file for seven-segment display functions
 *======================================== */
#include "project.h"

/** 
 * @brief Function to show a dot on both segments
 */
void Song_segment(uint8 index);

/** 
 * @brief Function to display 1 or 2 on both segments
 * @return An integer representing the displayed number
 */
void Volume_segment(int *index);

/** @} */ // end of group 

/* [] END OF FILE */
