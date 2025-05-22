#ifndef __FILTER_H__
#define __FILTER_H__

#include "buffer.h"

#ifndef __BUFFER_GENERIC__

typedef struct {
    buffer_t *input_buffer;
    buffer_t *output_buffer;

    uint32_t order;
    BUFFER_DATATYPE *coefficient;
} filter_fir_t;

int filter_fir_init(filter_fir_t *fil, uint32_t order);
int filter_fir_free(filter_fir_t *fil);

int filter_fir_get_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof);
int filter_fir_set_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof);

int filter_fir_update(filter_fir_t *fil);

void filter_fir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof);
void filter_iir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof, uint32_t b_order, BUFFER_DATATYPE *b_fil_cof);

#endif

#endif