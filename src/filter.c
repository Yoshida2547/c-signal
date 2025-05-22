#include "filter.h"

int filter_fir_init(filter_fir_t *fil, buffer_t *input_buffer, buffer_t *output_buffer, uint32_t order) {
    if(fil == NULL) {
        FILTER_ERROR("ERROR: NULL pointer was given.\r\n");
        return -1;
    }

    if(input_buffer == NULL) {
        FILTER_ERROR("ERROR: Input buffer pointer must not be NULL.\r\n");
        return -1;
    }

    if(output_buffer == 0) {
        output_buffer = (buffer_t *) malloc(sizeof(buffer_t));
    }
}