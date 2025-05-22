#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define BUFFER_THROWN_ERROR 0

#define BUFFER_FROCE_POWER_OF_2 1

#if BUFFER_THROWN_ERROR  == 1
#define BUFFER_ERROR(msg, ...)  fprintf(stderr, msg, ##__VA_ARGS__)

#else
#define BUFFER_ERROR(msg, ...)

#endif

#define BUFFER_MODE 3

/*
    MODE:
        0 GENERIC

        1 INT16
        2 INT32
        3 FLOAT32
*/

#ifndef BUFFER_MODE
#define BUFFER_MODE 0
#endif

#if BUFFER_MODE == 0
#define __BUFFER_GENERIC__
#define BUFFER_DATATYPE void

#elif BUFFER_MODE == 1
#define __BUFFER_USE_INT16
#define BUFFER_DATATYPE int16_t

#elif BUFFER_MODE == 2
#define __BUFFER_USE_INT32
#define BUFFER_DATATYPE int32_t

#elif BUFFER_MODE == 3
#define __BUFFER_USE_FLOAT32
#define BUFFER_DATATYPE float

#endif

/*
    TODO: Make buffer for float int16 and int32
*/

typedef struct {
/*
    Structure description
*/
    size_t buffer_size;

#ifdef __BUFFER_GENERIC__
    size_t data_size;
#endif

/*
    Structure state
*/
    uint32_t head;
    uint32_t tail;

    BUFFER_DATATYPE *buffer;

} buffer_t;

/*
    Initialize the circular buffer. allocate memory for buffer. return 0 if suscess.
*/
#ifdef __BUFFER_GENERIC__

int buffer_init(buffer_t *buf, size_t buffer_size, size_t data_size);
int buffer_new(buffer_t *buf, size_t buffer_size, size_t data_size);

#else

int buffer_init(buffer_t *buf, size_t buffer_size);
int buffer_new(buffer_t *buf, size_t buffer_size);

#endif

void buffer_free(buffer_t *buf);

/*
    Generic Function
*/
int buffer_get(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t index);
int buffer_set(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t index);

int buffer_get_byte(buffer_t *buf, uint8_t *data, uint32_t index);
int buffer_set_byte(buffer_t *buf, uint8_t *data, uint32_t index);

/*
    Wrapper
*/
int circular_buf_push(buffer_t *buf, BUFFER_DATATYPE *data);
int circular_buf_pop(buffer_t *buf, BUFFER_DATATYPE *data);

int circular_buf_get_oldest(buffer_t *buf,  BUFFER_DATATYPE *data, int offset);
int circular_buf_get_newest(buffer_t *buf, BUFFER_DATATYPE *data, int offset);

void circular_buf_next(buffer_t *buf, uint32_t *ptr);
void circular_buf_prev(buffer_t *buf, uint32_t *ptr);

/*
    Helper
*/

void buffer_print(buffer_t *buf);

#endif