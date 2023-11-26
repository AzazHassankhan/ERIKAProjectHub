/*========================================
 *@game_file.c
 *@brief Your file brief description here
 *========================================*/

// Including necessary header files
#include "project.h"
#include "stdlib.h"
#include "time.h"
#include "segment_file.h"
#include "uART_file.h"
#include "timer_file.h"
#include "random_Delay_file.h"

/*========================================
               Defining states
 *========================================
*/

// Define a state enumeration for the game
typedef enum
{
    Game_Wait,         // State: Waiting for action
    Game_Press_button, // State: Waiting for button press
    Game_Time_out,     // State: Timeout occurred
    Game_exit,         // State: Game exit
} Game_state;

// Define a structure to hold game state
typedef struct
{
    Game_state state;  // State variable
} Game_t;

/*========================================
Creating game object to control state
 *========================================
*/

// Create a static game object
static Game_t Game_obj;

/*========================================
             Game Initialization
 *========================================
*/

// Function to initialize the game
void Game_Init()
{
    // Initializing game state and components
    Game_obj.state = Game_Wait; // Set initial state to "Wait"
    UART_init();                // Initialize UART
    isr_1_StartEx(button1);     // Start button interrupt
    srand(time(NULL));          // Seed initialization for random number
}

/*========================================
             State Machine 
 *========================================
*/

// Function to handle game state machine
void Game_Play()
{
    static int count = 0, correct = 0, exit_loop = 0, randomValue = 0;
    EventMaskType ev = 0; // Event variable

    // Main loop for the state machine
    while (!exit_loop)
    {
        // State machine switch-case
        switch (Game_obj.state)
        {
            case Game_Wait:
                // Check for button press to start
                WaitEvent(button);
                GetEvent(Game, &ev);
                ClearEvent(ev);
                if ((Button_1_Read() == 1) || (Button_2_Read() == 1))
                {
                    Game_obj.state = Game_Press_button;
                }
                else
                {
                    Game_obj.state = Game_Wait;
                }
                break;

            case Game_Press_button:
                // Activate segments, generate random value, and set up timeout
                seven_segment();
                SetRelAlarm(Alarm_3, random_value_generator(), 0);
                WaitEvent(sleepTask);
                GetEvent(Game, &ev);
                ClearEvent(ev);
                randomValue = Random_Num_segment();
                Game_obj.state = Game_Time_out;
                Timer_1_Start();
                break;

            case Game_Time_out:
                // Handle button press, calculate reaction time, and state transitions
                if ((Button_1_Read() == 1 && randomValue == 1) ||
                    (Button_2_Read() == 1 && randomValue == 2))
                {
                    UART_correct();
                    UART_time_reaction(reaction_time);
                    correct++;
                    Game_obj.state = Game_exit;
                }
                else if ((Button_1_Read() == 1 && randomValue != 1) ||
                         (Button_2_Read() == 1 && randomValue != 2))
                {
                    UART_wrong();
                    UART_time_reaction(reaction_time);
                    Game_obj.state = Game_exit;
                }
                else
                {
                    if (Slow())
                    {
                        UART_Slow();
                        Game_obj.state = Game_exit;
                    }
                    else
                    {
                        Game_obj.state = Game_Time_out;
                    }
                }
                break;

            case Game_exit:
                // Manage game rounds and exit conditions
                if (count < 9)
                {
                    Game_obj.state = Game_Wait;
                }
                else
                {
                    UART_final(correct, Total_time);
                    Game_obj.state = Game_exit;
                    exit_loop = 1;
                }
                count++;
                break;
        }
    }
}

/*[] END OF FILE */
