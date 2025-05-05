#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>

int circular_buffer_pointer_next(uint32_t *pointer, uint32_t size);
int circular_buffer_pointer_prev(uint32_t *pointer, uint32_t size);

uint32_t circular_buffer_index(uint32_t current, uint32_t buffer_size, uint32_t index);
void *circular_buffer_get(uint32_t current, uint32_t buffer_size, uint32_t index, void **buffer, __ssize_t size);

#endif