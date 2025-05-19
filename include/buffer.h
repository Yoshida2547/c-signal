#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
/*
    Structure description
*/
    size_t buffer_size;
    size_t data_size;

/*
    Structure state
*/
    uint32_t head;
    uint32_t tail;

    void *buffer;

} buffer_t;

/*
    Initialize the circular buffer. allocate memory for buffer. return 0 if suscess.
*/
int buffer_init(buffer_t *buf, size_t buffer_size, size_t data_size);
void buffer_free(buffer_t *buf);

/*
    Generic Function
*/
int buffer_get(buffer_t *buf, void *data, uint32_t index);
int buffer_set(buffer_t *buf, void *data, uint32_t index);

int buffer_get_byte(buffer_t *buf, uint8_t *data, uint32_t index);
int buffer_set_byte(buffer_t *buf, uint8_t *data, uint32_t index);

/*
    Wrapper
*/
int circular_buf_push(buffer_t *buf, void *data);
int circular_buf_pop(buffer_t *buf, void *data);

int circular_buf_get_oldest(buffer_t *buf, void *data, uint32_t offset);
int circular_buf_get_newest(buffer_t *buf, void *data, uint32_t offset);

void circular_buf_next(buffer_t *buf, uint32_t *ptr);
void circular_buf_prev(buffer_t *buf, uint32_t *ptr);

/*
    Helper
*/

#endif