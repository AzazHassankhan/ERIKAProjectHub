/*========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 *========================================
 */

/**
 * @brief Function to start and show UART.
 */
void UART_init();

/**
 * @brief Function to show the wrong message on UART.
 */
void UART_correct();

/**
 * @brief Function to show the correct reaction on UART.
 */
void UART_wrong();

/**
 * @brief Function to show reaction timing on UART.
 * 
 * @param counter The counter value.
 */
void UART_time_reaction(int counter);

/**
 * @brief Function to show the final score message and total reaction time on UART.
 * 
 * @param correct The number of correct reactions.
 * @param Total_time The total reaction time.
 */
void UART_final(int correct, int Total_time);

/**
 * @brief This function is called when the reaction is too slow.
 */
void UART_Slow();
