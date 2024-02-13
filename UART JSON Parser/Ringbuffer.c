/*!
 * Ringbuffer.c
 * @brief Implementation of the ring buffer functionality
 * Created on: 15.12.2023
 * Author: Azaz Hassan Khan
 */

// Include standard library for memory allocation functions
#include <stdlib.h>

// Include header file for ring buffer functionality
#include "Ringbuffer.h"

// Include project-specific header file
#include "project.h"

// Initialize the ring buffer
RC_t RB_init(RB_t *const me, uint16_t size)
{
    // Set the size of the ring buffer
    me->m_size = size;

    // Allocate memory for the buffer
    me->m_pBuffer = (RB_content_t*) malloc(size * sizeof(RB_content_t));
    
    // If not enough memory
    if (me->m_pBuffer == NULL) 
        return RC_ERROR_NULL;
    else 
        return RC_SUCCESS;
    
}

// Deinitialize the ring buffer
RC_t RB_deinit(RB_t *const me)
{
    // Free memory allocated for the buffer
    free(me->m_pBuffer);

    // Return success status
    return RC_SUCCESS;
}

// Put data into the ring buffer
RC_t RB_put(RB_t *const me, RB_content_t data)
{
    // Check if the buffer is not full
    if (me->m_fillLevel < me->m_size)
    {
        // Get resource lock to ensure thread safety
        GetResource(res1);

        // Put data into the buffer
        me->m_pBuffer[me->m_writeIdx] = data;

        // Move the write index to the next position
        me->m_writeIdx++;

        // Wrap around the write index if needed
        me->m_writeIdx %= me->m_size;

        // Increase the fill level of the buffer
        me->m_fillLevel++;

        // Release the resource lock
        ReleaseResource(res1);

        // Return success status
        return RC_SUCCESS;
    }
    else
    {
        // Return error status if buffer is full
        return RC_ERROR_WRITE_FAILS;
    }

    // Return success status
    return RC_SUCCESS;
}

// Get data from the ring buffer
RC_t RB_get(RB_t *const me, RB_content_t *const data)
{
    // Check if the buffer is not empty
    if (me->m_fillLevel > 0)
    {
        // Get resource lock to ensure thread safety
        GetResource(res1);

        // Get data from the buffer
        *data = me->m_pBuffer[me->m_readIdx];

        // Move the read index to the next position
        me->m_readIdx++;

        // Wrap around the read index if needed
        me->m_readIdx %= me->m_size;

        // Decrease the fill level of the buffer
        me->m_fillLevel--;

        // Release the resource lock
        ReleaseResource(res1);

        // Return success status
        return RC_SUCCESS;
    }
    else
    {
        // Return error status if buffer is empty
        return RC_ERROR_READ_FAILS;
    }
}

// Clear the ring buffer
RC_t RB_clear(RB_t *const me)
{
    // Reset the fill level of the buffer
    me->m_fillLevel = 0;

    // Reset the read index of the buffer
    me->m_readIdx = 0;

    // Reset the write index of the buffer
    me->m_writeIdx = 0;

    // Return success status
    return RC_SUCCESS;
}