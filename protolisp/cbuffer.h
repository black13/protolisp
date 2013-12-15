#ifndef CBUFFER_H_
#define CBUFFER_H_

typedef BOOL   bool_t;
typedef unsigned char uint8_t;

// Represents a circular buffer.
#define BUFSIZE 30
typedef struct {
	unsigned char buf[BUFSIZE];
	unsigned char front, back;
} CircularBuffer;

/**
 * Initialize the given circular buffer.
 */
void circular_buffer_init(CircularBuffer* buf);

/**
 * Adds item to the buffer.
 *
 * Call circular_buffer_full to make sure this buffer is not full
 * first.
 */
void circular_buffer_push(CircularBuffer* buf, unsigned char data);

/**
 * Returns the current amount of bytes in the buffer.
 */
unsigned char circular_buffer_size(CircularBuffer* buf);

/**
 * Removes item from the buffer.
 * Returns zero if buffer is empty.
 */
unsigned char circular_buffer_pop(CircularBuffer* buf);

/**
 * Returns the byte at the given POSITIVE offset from the back of the buffer.
 * Returns zero if buffer is empty.
 */
unsigned char circular_buffer_peek(CircularBuffer* buf, int offset);

/**
 * Returns true if circular buffer is full.
 */
bool_t circular_buffer_full(CircularBuffer* buf);

/**
 * Returns true if circular buffer is empty.
 */
bool_t circular_buffer_empty(CircularBuffer* buf);


#endif /*CBUFFER_H_*/
