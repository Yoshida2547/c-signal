#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stdlib.h>

#define FROM_VOID_P(void_ptr, datatype) (datatype *) void_ptr
#define FROM_VOID(void_ptr, datatype) *(FROM_VOID_P(void_ptr, datatype))

#define TO_VOID_P(data) (void *) &(data)

#define CIRCULAR_PUSH(buffer, value, datatype) FROM_VOID(buffer_circular_push(&(buffer), TO_VOID(value, datatype)), datatype) ? 0

typedef struct {

    uint32_t    buffer_size;
    size_t      datatype_size;

    void *      buffer_ptr; /*Point to next buffer to write to.*/
    void **     buffer;

} Buffer;

// Generic function
Buffer *buffer_init(Buffer *, uint32_t buffer_size, size_t datatype_size);

// Circular buffer function
void * buffer_circular_push(Buffer *, void *);



#endif