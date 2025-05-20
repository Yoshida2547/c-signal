#include "buffer.h"

#ifdef __BUFFER_GENERIC__

int buffer_init(buffer_t *buf, size_t buffer_size, size_t data_size)

#else

int buffer_init(buffer_t *buf, size_t buffer_size)

#endif
{

    if(buf == NULL) return -1;
    if(buffer_size == 0) return -1;

#ifdef __BUFFER_GENERIC__
    if(data_size == 0) return -1;
#endif

    buf->buffer_size = buffer_size;

#ifdef __BUFFER_GENERIC__
    buf->data_size = data_size;

    size_t total_size = buffer_size*buf->data_size;
#else
    size_t total_size = buf->buffer_size*sizeof(BUFFER_DATATYPE);
#endif

    buf->buffer = (BUFFER_DATATYPE *) malloc(total_size);

    if(buf->buffer == NULL) {
        return -1;
    }

    buf->head = 0;
    buf->tail = 0;
    
    return 0;
}

void buffer_free(buffer_t *buf) {
    free(buf->buffer);
    free(buf);
}

int buffer_get(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;

#ifdef __BUFFER_GENERIC__

    memcpy(data, buf->buffer + buf->data_size*index, buf->data_size);

#else

    *data = buf->buffer[index];

#endif

    return 0;
}

int buffer_set(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;

#ifdef __BUFFER_GENERIC__

    memcpy(buf->buffer + buf->data_size*index, data, buf->data_size);

#else

    buf->buffer[index] = *data;

#endif

    return 0;
}

int buffer_get_byte(buffer_t *buf, uint8_t *data, uint32_t index) {
    if(data == NULL) return -1;

#ifdef __BUFFER_GENERIC__
    if(index > buf->buffer_size*buf->data_size - 1) return -1;

    *data = *( (uint8_t *) buf->buffer + index);
#else
    *data = ( (uint8_t *) buf->buffer)[index];
#endif

    return 0;
}

int buffer_set_byte(buffer_t *buf, uint8_t *data, uint32_t index) {
    if(data == NULL)                return -1;

#ifdef __BUFFER_GENERIC__
    if(index > buf->buffer_size*buf->data_size - 1)    return -1;

    *((uint8_t*) buf->buffer + index) = *data;
#else
    ( (uint8_t *) buf->buffer)[index] = *data;
#endif

    return 0;
}

int circular_buf_push(buffer_t *buf, BUFFER_DATATYPE *data) {
    int ret = 0;

    ret = buffer_set(buf, data, buf->head);

    if(ret) {
        return ret;
    }

    circular_buf_next(buf, &buf->head);

    return ret;
}

int circular_buf_pop(buffer_t *buf, BUFFER_DATATYPE *data) {
    int ret = 0;

    ret = buffer_get(buf, data, buf->tail);

    if(ret) {
        return ret;
    }

    circular_buf_next(buf, &buf->tail);

    return ret;
}

void circular_buf_next(buffer_t *buf, uint32_t *ptr) {
    if(*ptr < buf->buffer_size - 1) {
        *ptr += 1;
    } else {
        *ptr = 0;
    }

    return;
}

void circular_buf_prev(buffer_t *buf, uint32_t *ptr) {
    if(*ptr > 0) {
        *ptr -= 1;
    } else {
        *ptr = buf->buffer_size - 1;
    }

    return;
}
 
int circular_buf_get_oldest(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t offset) {
    if(data == NULL)                return -1; 
    if(offset > buf->buffer_size - 1) return -1; 

    uint32_t index = (buf->head + offset)%buf->buffer_size;

    buffer_get(buf, data, index);

    return 0;
}

int circular_buf_get_newest(buffer_t *buf, BUFFER_DATATYPE *data, uint32_t offset) {
    if(data == NULL)                return -1; 
    if(offset > buf->buffer_size - 1) return -1; 

    uint32_t index = buf->buffer_size - (offset - buf->head - 1)%buf->buffer_size - 1;

    printf("index: %d \r\n", index);

    buffer_get(buf, data, index);

    return 0;
}

#ifndef __BUFFER_GENERIC__

#include <stdio.h>

void buffer_print(buffer_t *buf) {
    printf("==================\r\n");
    for(uint32_t i = 0; i < 16; i++) {

        BUFFER_DATATYPE tmp = 0;
        buffer_get(buf, &tmp, i);

        if(i == buf->head) {
            printf("H>");
        } else {
            printf("  "); 
        }

#if defined __BUFFER_GENERIC__
        printf("%10x", tmp); 
#elif defined __BUFFER_USE_INT16
        printf("%10d", tmp); 
#elif defined __BUFFER_USE_INT32
        printf("%10d", tmp); 
#elif defined __BUFFER_USE_FLOAT32
        printf("%10.2f", tmp); 
#endif
        if(i == buf->tail) {
            printf("    <T\r\n");
        } else {
            printf("\r\n");
        }
    }
    printf("==================\r\n");
}

#endif


