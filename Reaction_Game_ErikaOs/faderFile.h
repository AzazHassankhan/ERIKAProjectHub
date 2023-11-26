/* ========================================
 *
 *Copyright YOUR COMPANY, THE YEAR
 *All Rights Reserved
 *UNPUBLISHED, LICENSED SOFTWARE.
 *
 *CONFIDENTIAL AND PROPRIETARY INFORMATION
 *WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */

/* ========================================
 *This Function Starts the 3 PWM components
 *========================================
 */
void PWM_Start_Func();
/* ========================================
 *This Function fades the 3 leds one after
   another.
 *========================================
*/
void PWM_Led_Fader_Func();

/**
 * @struct RG_Glow_t
 * @brief Structure to hold RGB values and time
 */
typedef struct {
    int red; ///< Red color value
    int green; ///< Green color value
    int blue; ///< Blue color value
    int timeInMS; ///< Time in milliseconds
} RG_Glow_t;

/**
 * @brief Function to handle LED glowing based on predefined configurations.
 * @details Glows the RGB LED based on predefined configurations with specified time intervals.
 */
void GlowerFunc();

/*[] END OF FILE */