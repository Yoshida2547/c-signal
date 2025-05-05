#include "buffer.h"

// Move to pointer to next position on buffer. 
// If its on the end of buffer then move to the begin.
int circular_buffer_pointer_next(uint32_t *pointer, uint32_t size) {

    // Check if input is valid.
    if(size == 0) return -1;
    if(*pointer >= size) return -1;

    if(*pointer == size - 1) {
        *pointer = 0;
    } else {
        *pointer = *pointer + 1;
    }
    return 0;
}

// Move to pointer to previos position on buffer. 
// If its on the begin of buffer then move to end of buffer.
int circular_buffer_pointer_prev(uint32_t *pointer, uint32_t size) {

     // Check if input is valid.
    if(*pointer >= size) return -1;
    if(size == 0) return -1;

    if(*pointer == 0) {
        *pointer = size - 1;
    } else {
        *pointer = *pointer - 1;
    }
    return 0;
}

// Return the index on circular buffer that correspond to order.
// Example: index=0 -> return oldest element on buffer,
// Example: index=size of buffer-1 -> return newest element on buffer,
uint32_t circular_buffer_index(uint32_t current, uint32_t size, uint32_t index)  {
    return (current + index)%size;
}

void *circular_buffer_get(
    uint32_t current, uint32_t buffer_size, uint32_t index, 
    void **buffer, __ssize_t size) {
    return buffer[size*circular_buffer_index(current, buffer_size, index)];
}