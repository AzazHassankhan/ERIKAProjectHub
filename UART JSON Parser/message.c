
// Include standard library for memory allocation
#include <stdlib.h>

// Include header file for message functionality
#include "message.h"

// Include header file for drawer functionality
#include "drawer.h"

// Initialize the message box
RC_t MSG_init(MSG_messagebox_t *const me, uint16_t const size, EventMaskType const ev, TaskType const task)
{
    // Set the size of the message box
    me->m_size = size;

    // Initialize the read index
    me->m_readIdx = 0;

    // Initialize the fill level
    me->m_fillLevel = 0;

    // Initialize the write index
    me->m_writeIdx = 0;

    // Set the event associated with a new message
    me->m_ev = ev;

    // Set the receiver task of the event
    me->m_task = task;

    // Allocate memory for the message buffer
    me->my_message = (message_t*)malloc(me->m_size * sizeof(message_t));

    // If not enough memory
    if (me->my_message == NULL) 
        return RC_ERROR_NULL;
    else 
        return RC_SUCCESS;
}

// Send a message
RC_t MSG_sendMessage(MSG_messagebox_t *const me, void const* const pData, uint16_t const size)
{
    // If the message box is not full
    if (me->m_fillLevel < me->m_size)    
    {
        // Set the size of the message
        me->my_message[me->m_writeIdx].m_size = size;

        // Allocate memory for the message data
        me->my_message[me->m_writeIdx].m_pBuffer = (Drawer_t*)malloc(size);    

        // Copy the message data
        *(Drawer_t*)me->my_message[me->m_writeIdx].m_pBuffer = *((Drawer_t*)pData);
        
        // Increment the fill level
        me->m_fillLevel++;
        
        // Move the write index
        me->m_writeIdx++;
        
        // Wrap around if necessary
        me->m_writeIdx %= me->m_size;
        
        // Set the event for the receiver task
        SetEvent(me->m_task, me->m_ev);
        
        return RC_SUCCESS;
    }
    else
    {
        return RC_ERROR_BUFFER_FULL;
    }
}

// Get the size of the next message in the buffer
RC_t MSG_getSizeOfNextMessage(MSG_messagebox_t *const me, uint16_t *const size)
{
    // If there is a message in the buffer
    if (me->my_message[me->m_readIdx].m_pBuffer != 0)
    {
        // Get the size of the next message
        *size = me->my_message[me->m_readIdx].m_size;
        
        return RC_SUCCESS;
    } 
    else 
    {
        // Set size to 0 if there is no message
        *size = 0;
        return RC_ERROR_NULL;
    }
}

// Wait for the next message
RC_t MSG_waitNextMessage(MSG_messagebox_t *const me)
{
    // Define event mask variable
    EventMaskType ev = 0;
    
    // Wait for the event
    WaitEvent(me->m_ev);
    
    // Get the event
    GetEvent(me->m_task, &ev);
    
    // Clear the event
    ClearEvent(ev); 
    
    return RC_SUCCESS;
}

// Receive a message
RC_t MSG_receiveMessage(MSG_messagebox_t *const me, void* pData, uint16_t const size)
{
    // If there are messages in the buffer
    if (me->m_fillLevel > 0)
    {
        // Read out data from the ring buffer
        if (me->my_message[me->m_readIdx].m_size >= size)
        {
            // Copy the message data
            *((Drawer_t*)pData) = *(Drawer_t*)me->my_message[me->m_readIdx].m_pBuffer;
        }
        
        // Free memory of m_pBuffer
        free(me->my_message[me->m_readIdx].m_pBuffer);
        
        // Move the read index
        me->m_readIdx++;
        
        // Wrap around if necessary
        me->m_readIdx %= me->m_size;
        
        // Decrement the fill level
        me->m_fillLevel--;
        
        return RC_SUCCESS;
    }
    
    return RC_ERROR_BUFFER_EMTPY;
}
