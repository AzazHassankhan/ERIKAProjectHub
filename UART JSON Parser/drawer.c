#include "project.h"               // Include header file for the project
#include "global.h"                // Include header file for global definitions
#include <stdio.h>                 // Include standard I/O library
#include <stdlib.h>                // Include standard library for memory allocation
#include "drawer.h"                // Include header file for drawer functionality
#include "parser.h"                // Include header file for parser functionality

// Define a structure to hold color string and corresponding integer value
typedef struct                     
{
    // Pointer to color string
    char *color_string;           
    
    // Integer value corresponding to the color string
    TFT_colors_t color_int;       
} LookupTable;                    

// Typedef for the structure as LookupTable
static const LookupTable colorTable[21] = {    

    // Initialize color mappings
    {"white",       WHITE},       
    {"black",       BLACK},
    {"blue",        BLUE},
    {"bred",        BRED},
    {"gred",        GRED},
    {"gblue",       GBLUE},
    {"red",         RED},
    {"magenta",     MAGENTA},
    {"green",       GREEN},
    {"cyan",        CYAN},
    {"yellow",      YELLOW},
    {"brown",       BROWN},
    {"brred",       BRRED},
    {"gray",        GRAY},
    {"darkblue",    DARKBLUE},
    {"lightblue",   LIGHTBLUE},
    {"grayblue",    GRAYBLUE},
    {"lightgreen",  LIGHTGREEN},
    {"lgray",       LGRAY},
    {"lgrayblue",   LGRAYBLUE},
    {"lbblue",      LBBLUE}
};

// Define function to retrieve next draw command
RC_t DRAWER_getNextDrawCommand(Drawer_t *const me, Parser_t *const parser)   
{
    // Define a token variable for storing the next token from the parser
    jsmntok_t NextToken;    
    
    // Check if getting the next token from the parser is successful
    if (PARSER_getNextToken(parser, &NextToken) == RC_SUCCESS)    
    {
        // Define an array to hold token data with a maximum size of 200 characters
        char Token_data[200] = "";    
        
        // Copy token data from parser content to Token_data
        strncpy(Token_data, parser->content + NextToken.start, NextToken.end - NextToken.start);   

        // Define a command string
        char command[] = "d";     
        // Define a color string
        char color[] = "c";       

        // Check if the token data matches the color string
        if (strcmp(Token_data, color) == 0)    
        {
            // Set the command type to DRAWER_CMD_COLOR
            me->command = DRAWER_CMD_COLOR;    
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken);    
            
            // Initialize a boolean flag to indicate if color is set to FALSE
            boolean_t color_is_set = FALSE;    
            
            // Loop through the color table
            for (unsigned int i = 0; i < sizeof(colorTable); i++)   
            {
                // Define a color value string
                char color_value[] = "";    
                
                // Copy token data to Token_data
                strncpy(Token_data, parser->content + NextToken.start, NextToken.end - NextToken.start);   
                
                // Check if token data matches a color string from the table
                if (strcmp(Token_data, colorTable[i].color_string) == 0)   
                {
                    // Set the color value in drawer data
                    me->data.color = colorTable[i].color_int;    
                    // Set color_is_set flag to TRUE
                    color_is_set = TRUE;    
                }
            }
            // If color is not set
            if (color_is_set == FALSE)    
            {
                // Set default color to BLACK
                me->data.color = BLACK;    
            }
        }

        // Check if the token data matches the command string
        else if (strcmp(Token_data, command) == 0)    
        {
            // Set the command type to DRAWER_CMD_DRAW
            me->command = DRAWER_CMD_DRAW;    
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken);    
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken);    
            
            // Define an array to hold x-coordinate
            char x1[5] = "";    
            
            // Copy x-coordinate from parser content to x1
            strncpy(x1, parser->content + NextToken.start, NextToken.end - NextToken.start);   
            
            // Convert x-coordinate to integer and store in drawer data
            me->data.coordinate[0] = atoi(x1);    
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken);    
            
            // Define an array to hold y-coordinate
            char y1[5] = "";    
            // Copy y-coordinate from parser content to y1
            strncpy(y1, parser->content + NextToken.start, NextToken.end - NextToken.start);   
            
            // Convert y-coordinate to integer and store in drawer data
            me->data.coordinate[1] = atoi(y1);
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken); 
            
            // Define an array to hold x2-coordinate
            char x2[5] = "";    
            
            // Copy x2-coordinate from parser content to x2
            strncpy(x2, parser->content + NextToken.start, NextToken.end - NextToken.start);   
            
            // Convert x2-coordinate to integer and store in drawer data
            me->data.coordinate[2] = atoi(x2);    
            
            // Get the next token from the parser
            PARSER_getNextToken(parser, &NextToken);    
            
            // Define an array to hold y2-coordinate
            char y2[5] = "";    
            
            // Copy y-coordinate from parser content to y2
            strncpy(y2, parser->content + NextToken.start, NextToken.end - NextToken.start);   
            
            // Convert y2-coordinate to integer and store in drawer data
            me->data.coordinate[3] = atoi(y2); 
        }
        
        else
        {
            return RC_ERROR;
        }
        
        return RC_SUCCESS;
    }
    
    else
    {
        return RC_ERROR;
    }
}