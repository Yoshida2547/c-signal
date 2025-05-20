#ifndef __FILTER_H__
#define __FILTER_H__

#include "buffer.h"

#ifndef __BUFFER_GENERIC__

void filter_fir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof);
void filter_iir_apply(buffer_t *input, buffer_t *output, uint32_t f_order, BUFFER_DATATYPE *f_fil_cof, uint32_t b_order, BUFFER_DATATYPE *b_fil_cof);

#endif

#endif