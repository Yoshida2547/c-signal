#include "buffer.h"

int buffer_init(buffer_t *buf, size_t buffer_size, size_t data_size) {

    if(buf == NULL) return -1;
    if(buffer_size == 0 || data_size == 0) return -1;

    buf->buffer_size = buffer_size;
    buf->data_size = data_size;

    size_t total_size = buf->buffer_size*buf->data_size;

    buf->buffer = (uint8_t *) malloc(total_size);

    if(buf->buffer == NULL) {
        return -1;
    }

    uint8_t tmp = 0;

    for(uint32_t i = 0; i < buf->buffer_size*buf->data_size; i++) {
        buffer_set_byte(buf, &tmp, i);
    }

    buf->head = 0;
    buf->tail = 0;
    
    return 0;
}

void buffer_free(buffer_t *buf) {
    free(buf->buffer);
    free(buf);
}

int buffer_get(buffer_t *buf, void *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;

    memcpy(data, buf->buffer + buf->data_size*index, buf->data_size);

    return 0;
}

int buffer_set(buffer_t *buf, void *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;

    memcpy(buf->buffer + buf->data_size*index, data, buf->data_size);

    return 0;
}

int buffer_get_byte(buffer_t *buf, uint8_t *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;


    *data = *( (uint8_t *) buf->buffer + index);

    return 0;
}

int buffer_set_byte(buffer_t *buf, uint8_t *data, uint32_t index) {
    if(data == NULL)                return -1;
    if(index > buf->buffer_size - 1)    return -1;

    *((uint8_t*) buf->buffer + index) = *data;

    return 0;
}

int circular_buf_push(buffer_t *buf, void *data) {
    int ret = 0;

    ret = buffer_set(buf, data, buf->head);

    if(ret) {
        return ret;
    }

    circular_buf_next(buf, &buf->head);

    return ret;
}

int circular_buf_pop(buffer_t *buf, void *data) {
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
 
int circular_buf_get_oldest(buffer_t *buf, void *data, uint32_t offset) {
    if(data == NULL)                return -1; 
    if(offset > buf->buffer_size - 1) return -1; 

    uint32_t index = (buf->head + offset)%buf->buffer_size;

    buffer_get(buf, data, index);

    return 0;
}

int circular_buf_get_newest(buffer_t *buf, void *data, uint32_t offset) {
    if(data == NULL)                return -1; 
    if(offset > buf->buffer_size - 1) return -1; 

    uint32_t index = buf->buffer_size - (offset - buf->head)%buf->buffer_size - 1;

    buffer_get(buf, data, index);

    return 0;
}
