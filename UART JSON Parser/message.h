#include "global.h"               // Include header file for global definitions
#include "project.h"              // Include header file for the project
#include "Ringbuffer.h"           // Include header file for ring buffer functionality

#define POSTBOX_SIZE 10           // Define the size of the postbox

typedef struct {                 // Define a structure to represent a message
    uint16 m_size;               // Size of the message
    void * m_pBuffer;            // Pointer to the message buffer
} message_t;                     // Typedef for the structure as message_t

typedef struct {                 // Define a structure to represent a message box
    message_t * my_message;      // Pointer to the message in the box
    uint16_t m_size;             // Size of the message box
    uint16_t m_readIdx;          // Index to read from the message box
    uint16_t m_writeIdx;         // Index to write to the message box
    uint16_t m_fillLevel;        // Fill level of the message box
    EventMaskType m_ev;          // Event mask for the message box
    TaskType m_task;             // Task associated with the message box
} MSG_messagebox_t;              // Typedef for the structure as MSG_messagebox_t

/**
* @brief Initializes the message box.
* 
* Initializes the ring buffer and sets up the memory for the metadata.
* 
* @param me Pointer to the MSG_messagebox_t object.
* @param size Size of the ring buffer.
* @param ev Event to be fired in case of a new message.
* @param task Receiver task of the event.
* @return RC_t RC_SUCCESS in case of no error else error code.
*/
RC_t MSG_init(MSG_messagebox_t *const me, uint16_t const size, EventMaskType const ev, TaskType const task);

/**
* @brief Sends a message.
* 
* Creates a temporary transfer buffer, copies the data into this buffer,
* and fires an event to the receiver task.
* 
* @param me Pointer to the MSG_messagebox_t object.
* @param pData Pointer to the data to be transmitted.
* @param size Size of the transmitted data.
* @return RC_t RC_SUCCESS in case of no error else error code.
*/
RC_t MSG_sendMessage(MSG_messagebox_t *const me, void const* const pData, uint16_t const size);

/**
* @brief Returns the size of the next message in the buffer.
* 
* Required for providing storage on the receiver side.
* 
* @param me Pointer to the MSG_messagebox_t object.
* @param size Pointer to store the size of the next message.
* @return RC_t RC_SUCCESS in case of no error else error code.
*/
RC_t MSG_getSizeOfNextMessage(MSG_messagebox_t *const me, uint16_t *const size);

/**
* @brief Waits for the next message.
* 
* Uses OS services to wait for the next message.
* 
* @param me Pointer to the MSG_messagebox_t object.
* @return RC_t RC_SUCCESS in case of no error else error code.
*/
RC_t MSG_waitNextMessage(MSG_messagebox_t *const me);

/**
* @brief Reads the message from the transfer buffer and releases the allocated memory.
* 
* @param me Pointer to the MSG_messagebox_t object.
* @param pData Pointer to the memory for storing the received message.
* @param size Size of the received message.
* @return RC_t RC_SUCCESS in case of no error else error code.
*/
RC_t MSG_receiveMessage(MSG_messagebox_t *const me, void* pData, uint16_t const size);
