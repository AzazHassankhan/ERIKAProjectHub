/*
 *   Lab 2
 *   V1.0
 *   Azaz Hassan Khan
 */

// Include project-specific header file
#include "project.h"

// Include header file for ring buffer implementation
#include "Ringbuffer.h"

// Include header file for JSON parsing library
#include "jsmn.h"

// Include header file for parser functionality
#include "parser.h"

// Include header file for drawing functionality
#include "drawer.h"

// Include header file for message passing
#include "message.h"

// Include header file for TFT display
#include "tft.h"

// Declare a ring buffer object for storing incoming data
RB_t buffer_value;

// Declare a parser object to parse JSON data
Parser_t myParser;

// Declare a message box for passing drawing commands
MSG_messagebox_t myMessageBox = {};

// Main function
int main(void)
{
    // Enable global interrupts
    CyGlobalIntEnable;

    // Start the operating system
    for (;;)
        StartOS(OSDEFAULTAPPMODE);
}

// Task for initialization
TASK(task_init)
{
    // Start UART for logging
    UART_LOG_Start();

    // Initialize TFT display
    TFT_init();

    // Set TFT backlight intensity
    TFT_setBacklight(100);

    // Initialize system-specific functionality
    EE_system_init();

    // Initialize the ring buffer with a size of 200 bytes
    RB_init(&buffer_value, 200);

    // Initialize the message box
    MSG_init(&myMessageBox, POSTBOX_SIZE, ev_message, tsk_hmi);

    // Initialize the parser object
    PARSER_init(&myParser);

    // Activate task for JSON processing
    ActivateTask(tsk_json);

    // Activate task for handling the HMI
    ActivateTask(tsk_hmi);

    // Terminate the initialization task
    TerminateTask();
}


// Task for JSON processing
TASK(tsk_json)
{
    // Declare an event mask variable
    EventMaskType ev = 0;

    // Declare a variable to store the fill level of the ring buffer
    int fill;

    // Declare a variable to store data from the ring buffer
    RB_content_t data;

    // Loop indefinitely
    while (1)
    {
        // Wait for end of string event
        WaitEvent(end_string);

        // Get the event
        GetEvent(tsk_json, &ev);

        // Clear the event
        ClearEvent(ev);

        // Get the fill level of the ring buffer
        fill = buffer_value.m_fillLevel;

        // Iterate over the data in the ring buffer
        for (int i = 0; i < fill; i++)
        {
            // Get data from the ring buffer
            if (RB_get(&buffer_value, &data) != RC_SUCCESS)
            {
                // Clear the ring buffer if data retrieval fails
                RB_clear(&buffer_value);
            }
            else
            {
                // Add character to the parser
                PARSER_addChar(&myParser, data);
            }
        }

        // Parse the JSON data
        if (PARSER_parse(&myParser) == RC_SUCCESS)
        {
            // Process all tokens in the parser
            while (myParser.nextToken < myParser.numberOfToken)
            {
                // Declare a drawer object
                Drawer_t myDrawer;

                // Get the next drawing command
                if(DRAWER_getNextDrawCommand(&myDrawer, &myParser)==RC_ERROR){continue;}

                // Send the drawing command via message box
                MSG_sendMessage(&myMessageBox, &myDrawer, sizeof(Drawer_t));
            }
        }
        // Clear the parser data
        PARSER_clear(&myParser);
    }

    // Terminate the JSON processing task
    TerminateTask();
}


// Task for handling the HMI
TASK(tsk_hmi)
{
    // Initialize color variable with white
    TFT_colors_t color = WHITE;

    // Declare a drawer command variable
    Drawer_t command;
    
    // Clear the TFT screen
    TFT_clearScreen();
    
    // Loop indefinitely
    while (1)
    {

        // Wait for the next message in the message box
        MSG_waitNextMessage(&myMessageBox);

        // Receive messages from the message box
        while (MSG_receiveMessage(&myMessageBox, &command, sizeof(Drawer_t)) == RC_SUCCESS)
        {
            // Check if the command is to set color
            if (command.command == DRAWER_CMD_COLOR)
            {
                // Update the current color
                color = command.data.color;
            }
            // Check if the command is to draw
            else if (command.command == DRAWER_CMD_DRAW)
            {
                // Draw a line on the TFT screen
                TFT_writeLine(command.data.coordinate[0], command.data.coordinate[1], command.data.coordinate[2], command.data.coordinate[3], color);
            }
        }
    }
}

// Interrupt service routine when received bytes on UART
ISR2(UART_ISR)
{
    // Get character from UART
    RB_content_t data = UART_LOG_GetChar();

    // Check if the character is the end of string marker
    if (data == 0)
    {
        // Set the end of string event for JSON processing task
        SetEvent(tsk_json, end_string);
    }
    else
    {
        // Put character into the ring buffer
        if (RB_put(&buffer_value, data) != RC_SUCCESS)
        {
            // Clear the ring buffer if putting data fails
            RB_clear(&buffer_value);
        }
    }
}

/* [] END OF FILE */