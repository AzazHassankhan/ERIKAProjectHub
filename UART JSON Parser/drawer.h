
#ifndef DRAWER_H
#define DRAWER_H

#include "parser.h"
#include "Ringbuffer.h"
#include "tft.h"

/**
 * @brief Enumeration representing different types of drawer commands.
 */
typedef enum {
    NONE, /**< No command */
    DRAWER_CMD_COLOR, /**< Command to set color */
    DRAWER_CMD_DRAW /**< Command to draw */
} Drawer_commandType_t;

/**
 * @brief Structure representing a drawer command.
 */
typedef struct  {
    Drawer_commandType_t command; /**< The type of command */
    union
    {
        TFT_colors_t color; /**< Color value for DRAWER_CMD_COLOR */
        uint8_t coordinate[4]; /**< Coordinates for DRAWER_CMD_DRAW */
    } data; /**< Union containing command data */
} Drawer_t;


/**
 * @brief Retrieves the next draw command from the parser.
 * 
 * Translates a JSON tag into a command type for the TFT.
 * 
 * @param me Pointer to the Drawer_t object to store the next command.
 * @param parser Pointer to the Parser_t object from which to retrieve the command.
 * @return RC_SUCCESS if a command was found, RC_ERROR_BUFFER_EMTPY if parsing has come to an end, other error code as required.
 */
RC_t DRAWER_getNextDrawCommand(Drawer_t *const me, Parser_t *const parser);

#endif /* DRAWER_H */

