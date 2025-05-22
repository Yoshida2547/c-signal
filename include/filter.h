#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"

#ifndef __FILTER_H__
#define __FILTER_H__

#define FILTER_THROWN_ERROR 0

#if FILTER_THROWN_ERROR == 1
#define FILTER_ERROR(msg, ...)  fprintf(stderr, msg, ##__VA_ARGS__)

#else
#define FILTER_ERROR(msg, ...)

#endif

#define FREE_BUF_INPUT  1 << 0
#define FREE_BUF_OUTPUT 1 << 0

#define FREE_BUF_ALL    FREE_BUF_INPUT | FREE_BUF_OUTPUT

#ifndef __BUFFER_GENERIC__

typedef struct {
    buffer_t *input_buffer;
    buffer_t *output_buffer;

    uint32_t order;
    BUFFER_DATATYPE *coefficient;
} filter_fir_t;

int filter_fir_init(filter_fir_t *fil, buffer_t *input_buffer, buffer_t *output_buffer, uint32_t order);
void filter_fir_free(filter_fir_t *fil, char OPTIONS);

int filter_fir_get_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof);
int filter_fir_set_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof);

int filter_fir_update(filter_fir_t *fil);

void filter_fir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof);
void filter_iir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof, uint32_t b_order, BUFFER_DATATYPE *b_fil_cof);

#endif

#endif