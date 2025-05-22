#include "filter.h"

int filter_fir_init(filter_fir_t *fil, buffer_t *input_buffer, buffer_t *output_buffer, uint32_t order) {
    if(order == 0) {
        FILTER_ERROR("ERROR: Filter order must greater than ZERO.\r\n");
        return -1;
    }

    if(fil == NULL) {
        FILTER_ERROR("ERROR: NULL pointer was given.\r\n");
        return -1;
    }

    if(input_buffer == NULL) {
        FILTER_ERROR("ERROR: Input buffer pointer must not be NULL.\r\n");
        return -1;
    }

    if(output_buffer == NULL) {
        buffer_new(output_buffer, (size_t) order);
    }

    fil->input_buffer = input_buffer;
    fil->output_buffer = output_buffer;

    fil->order = order;

    fil->coefficient = (BUFFER_DATATYPE *) malloc(sizeof(BUFFER_DATATYPE)*order);

    if(fil->coefficient == NULL) {
        FILTER_ERROR("ERROR: Fail to allocate memory for coefficient.\r\n");
        return -1;
    }

    return 0;
}

void filter_fir_free(filter_fir_t *fil, char OPTIONS) {
    if(OPTIONS && FREE_BUF_INPUT) {
        free(fil->input_buffer);
    }

    if(OPTIONS && FREE_BUF_OUTPUT) {
        free(fil->output_buffer);
    }

    free(fil);
}

int filter_fir_get_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof) {

    if(cof == NULL) {
        return -1;
    }

    if(fil == NULL) {
        return -1;
    }

    memcpy(cof, fil->coefficient, fil->order);

    return 0;
}

int filter_fir_set_coeficient(filter_fir_t *fil, BUFFER_DATATYPE *cof) {

    if(cof == NULL) {
        return -1;
    }

    if(fil == NULL) {
        return -1;
    }

    memcpy(fil->coefficient, cof, fil->order);

    return 0;
}

int filter_fir_update(filter_fir_t *fil) {

    if(fil == NULL) {
        return -1;
    }

    BUFFER_DATATYPE result = 0;

    for(int i = 0; i < fil->order; i++) {
        BUFFER_DATATYPE tmp = 0;
        circular_buf_get_newest(fil->input_buffer, &tmp, i);

        result += fil->coefficient[i]*tmp;
    }

    circular_buf_push(fil->output_buffer, &result);

    return 0;
}