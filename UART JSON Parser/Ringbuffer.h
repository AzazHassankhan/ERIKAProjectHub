/*
 *Ringbuffer.h
 *
 *Created on: 15.12.2023
 *     Author: Azaz Hassan Khan
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include "global.h"
#define POSTBOX_SIZE 10

typedef unsigned char RB_content_t;

typedef struct
{
	RB_content_t * m_pBuffer;
	uint16_t m_size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
}

RB_t;

/**
 *Initialize data of ring buffer
 *\param RB_t *const me        -[OUT] the ring buffer object
 *\param uint16_t              -[IN] size of ring buffer
 *\return RC_SUCCESS
 */
RC_t RB_init(RB_t *const me, uint16_t size);

/**
 *free dynamic allocation
 *\param RB_t *const me        -[OUT] the ring buffer object
 *\return RC_SUCCESS
 */
RC_t RB_deinit(RB_t *const me);

/**
 *Put data inside ring buffer
 *\param RB_t *const me        -[OUT] the ring buffer object
 *\param RB_content_t data     -[IN] Data to be put in
 *\return RC_SUCCESS if successful, error code otherwise
 */
RC_t RB_put(RB_t *const me, RB_content_t data);

/**
 *Get data from ring buffer
 *\param RB_t *const me            -[OUT] the ring buffer object
 *\param RB_content_t *const data  -[OUT] data from ring buffer
 *\return RC_SUCCESS if successful, error code otherwise
 */
RC_t RB_get(RB_t *const me, RB_content_t *const data);

/**
 *clear data of Ring buffer
 *\param RB_t *const me        -[OUT] the ring buffer object
 *\return RC_SUCCESS
 */
RC_t RB_clear(RB_t *const me);


#endif /*RINGBUFFER_H_ */