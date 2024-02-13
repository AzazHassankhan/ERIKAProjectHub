// Defines the JSMN_HEADER
#define JSMN_HEADER
// Includes the jsmn.h header file
#include "jsmn.h"
	// Includes the parser.h header file
#include "parser.h"
	// Includes the standard input/output header file
#include <stdio.h>
	// Includes the standard library header file
#include <stdlib.h>
	// Includes the string manipulation header file
#include <string.h>
	// Includes the project-specific header file
#include "project.h"

// Declares a static variable to hold the next token
static jsmntok_t nextToken;

// Initializes the parser object.
RC_t PARSER_init(Parser_t *const me)
{
	// Initializes the JSON parser
	jsmn_init(&me->parser);
	// Clears the content buffer
	memset(me->content, '\0', sizeof(me->content) / sizeof(me->content[0]));
	// Resets the next free position
	me->nextFreePos = 0;
	// Resets the next token index
	me->nextToken = 0;
	// Resets the number of tokens
	me->numberOfToken = 0;
	// Returns success status
	return RC_SUCCESS;
}

// Clears the parser object.
RC_t PARSER_clear(Parser_t *const me)
{
	// Initializes the JSON parser
	jsmn_init(&me->parser);
    // Clears the content buffer
	memset(me->content, '\0', sizeof(me->content) / sizeof(me->content[0]));
	// Resets the next free position
	me->nextFreePos = 0;
	// Resets the next token index
	me->nextToken = 0;
	// Returns success status
	return RC_SUCCESS;
}

// Adds a character to the content buffer.
RC_t PARSER_addChar(Parser_t *const me, char data)
{
	// Appends the character to the content buffer
	strncat(me->content, &data, 1);
    
    return RC_SUCCESS;
}

// Adds a newline character to the content buffer.
RC_t PARSER_addEndl(Parser_t *const me)
{
	// Appends a newline character to the content buffer
	strncat(me->content, "\n", 1);
    
    return RC_SUCCESS;
}

// Retrieves the next token from the parser object.
RC_t PARSER_getNextToken(Parser_t *const me, jsmntok_t *const token)
{
	// Checks if there are remaining tokens
	if (me->nextToken < me->numberOfToken)
	{
		// Copies token information
		token->type = me->token[me->nextToken].type;
		token->start = me->token[me->nextToken].start;
		token->end = me->token[me->nextToken].end;
		token->size = me->token[me->nextToken].size;
		// Increments the token index
		me->nextToken++;
		// Returns success status
		return RC_SUCCESS;
	}
	else
	{
		// Returns error status if no more tokens are available
		return RC_ERROR;
	}
}

// Parses the content buffer and processes each token.
RC_t PARSER_parse(Parser_t *const me)
{
	// Parses the content buffer and retrieves the number of tokens
	me->numberOfToken = jsmn_parse(&(me->parser), me->content, strlen(me->content), me->token, sizeof(me->token) / sizeof(me->token[0]));

	// Checks if the number of tokens indicates a  error
	if (me->numberOfToken <0)
	{
		UART_LOG_PutString("Invalid string!!!");
        me->nextToken = 0;
        return RC_ERROR;
	}

    
	else
	{
		// Initializes a counter
		int i = 0;
		// Iterates through each token
		while (PARSER_getNextToken(me, &nextToken) == RC_SUCCESS)
		{
			// Handles different token types
			if (nextToken.type == JSMN_OBJECT)
			{
			 	// Processes object tokens
				char name[200] = "tsk_json : Parsed token ";
				char token_number[3] = "";
				itoa(i, token_number, 10);
				char token_type[20] = "-JSMN_OBJECT: ";
				strcat(name, token_number);
				strcat(name, token_type);
				UART_LOG_PutString(name);
				PARSER_dbg_printToken(me);
				
			}
			else if (nextToken.type == JSMN_ARRAY)
			{
			 	// Processes array tokens
				char name[200] = "tsk_json : Parsed token ";
				char token_number[3] = "";
				itoa(i, token_number, 10);
				char token_type[20] = "-JSMN_ARRAY: ";
				strcat(name, token_number);
				strcat(name, token_type);
				UART_LOG_PutString(name);
				PARSER_dbg_printToken(me);
			
			}
			else if (nextToken.type == JSMN_STRING)
			{
			 	// Processes string tokens
				char name[200] = "tsk_json : Parsed token ";
				char token_number[3] = "";
				itoa(i, token_number, 10);
				char token_type[20] = "-JSMN_STRING: ";
				strcat(name, token_number);
				strcat(name, token_type);
				UART_LOG_PutString(name);
				PARSER_dbg_printToken(me);
				
			}
			else if (nextToken.type == JSMN_PRIMITIVE)
			{
			 	// Processes primitive tokens
				char name[200] = "tsk_json : Parsed token ";
				char token_number[3] = "";
				itoa(i, token_number, 10);
				char token_type[20] = "-JSMN_PRIMITIVE: ";
				strcat(name, token_number);
				strcat(name, token_type);
				UART_LOG_PutString(name);
				PARSER_dbg_printToken(me);
				
			}
            
            else
            {
                return RC_ERROR;
            }
            
            i++;
		}
	}

	// Resets the token index
	me->nextToken = 0;
    
     return RC_SUCCESS;
}

// Debug function to print token data.
RC_t PARSER_dbg_printToken(Parser_t *const me)
{
	// Copies token data from the content buffer
	char token_data[200] = "";
    
    // Copies token data from the content buffer starting from the token's start position to its end position
	strncpy(token_data, me->content + nextToken.start, nextToken.end - nextToken.start);
	
    // Prints token data
	UART_LOG_PutString(token_data);
    
    UART_LOG_PutString("\n");
    
     return RC_SUCCESS;
}