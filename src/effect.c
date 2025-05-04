#include "effect.h"
#include "buffer.h"

#include <stdlib.h>

// Inital effect allocate buffer yadayada
uint32_t effect_init(Effect *pEffect, uint32_t n_buffer) {

    pEffect  = (Effect *) malloc(sizeof(Effect));

    // Memory Allocation error.
    if(pEffect == NULL) {
        return EFFECT_STATUS_ERROR;
    }

    pEffect->buffer_size = n_buffer;

    // Allocate Heap for buffer and store its address on effect struct.
    pEffect->input_buffer   = (__EFFECT_PRIVATE_NUMBER__ **) malloc(sizeof(__EFFECT_PRIVATE_NUMBER__));
    pEffect->output_buffer  = (__EFFECT_PRIVATE_NUMBER__ **) malloc(sizeof(__EFFECT_PRIVATE_NUMBER__));

    // Set inital address for buffer pointer.
    pEffect->input_pointer  = 0;
    pEffect->output_pointer  = 0;

    return EFFECT_STATUS_OK;
}

void effect_deinit(Effect *pEffect) {

    free(pEffect->input_buffer);
    free(pEffect->output_buffer);

    free(pEffect);

    return;
}

// Update input buffer when new sample is acquired.
__EFFECT_PRIVATE_NUMBER__ effect_input_update(Effect *pEffect, __EFFECT_PRIVATE_NUMBER__ input) {

    // Replace oldest sample in input buffer with input.
    *pEffect->input_buffer[pEffect->input_pointer] = input;

    // Move buffer point to next index (next oldest)
    circular_buffer_pointer_next(&pEffect->input_pointer, pEffect->buffer_size);

    return input;
}


// Update output buffer when calculation is done.
 __EFFECT_PRIVATE_NUMBER__ effect_output_update(Effect *pEffect, __EFFECT_PRIVATE_NUMBER__ output) {

    // Replace oldest sample in output buffer with output.
    *pEffect->output_buffer[pEffect->output_pointer] = output;

    // Move buffer point to next index (next oldest)
    circular_buffer_pointer_next(&pEffect->output_pointer, pEffect->buffer_size);

    return output;
}

__EFFECT_PRIVATE_NUMBER__ effect_get_input_sample  (Effect *pEffect, uint32_t index) {

    /*
        Get the element on bufffer return void pointer convert to int pointer (int *) and dereferance its to int
    */

    return *(
        (__EFFECT_PRIVATE_NUMBER__ *) circular_buffer_get(
            pEffect->input_pointer, 
            pEffect->buffer_size, 
            index, 
            (void **) pEffect->input_buffer, 
            sizeof(__EFFECT_PRIVATE_NUMBER__)
    ));
}
__EFFECT_PRIVATE_NUMBER__ effect_get_output_sample (Effect *pEffect, uint32_t index) {

    /*
        Get the element on bufffer return void pointer convert to int pointer (int *) and dereferance its to int
    */

    return *(
        (__EFFECT_PRIVATE_NUMBER__ *) circular_buffer_get(
            pEffect->output_pointer, 
            pEffect->buffer_size, 
            index, 
            (void **) pEffect->output_buffer, 
            sizeof(__EFFECT_PRIVATE_NUMBER__)
    ));
}

