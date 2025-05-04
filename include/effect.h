#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <stdint.h>

#define EFFECT_BIT_DEPTH_8BIT   0x00
#define EFFECT_BIT_DEPTH_10BIT  0x01
#define EFFECT_BIT_DEPTH_12BIT  0x02
#define EFFECT_BIT_DEPTH_16BIT  0x03
#define EFFECT_BIT_DEPTH_20BIT  0x04
#define EFFECT_BIT_DEPTH_24BIT  0x05
#define EFFECT_BIT_DEPTH_32BIT  0x06

#define EFFECT_BIT_DEPTH_32FLOAT 0x07

#define EFFECT_BIT_DEPTH EFFECT_BIT_DEPTH_16BIT

#if EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_8BIT

#define __EFFECT_PRIVATE_NUMBER__ int8_t

#elif \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_10BIT || \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_12BIT || \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_16BIT

#define __EFFECT_PRIVATE_NUMBER__ int16_t

#elif \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_20BIT || \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_24BIT || \
EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_32BIT

#define __EFFECT_PRIVATE_NUMBER__ uint32_t

#elif EFFECT_BIT_DEPTH == EFFECT_BIT_DEPTH_32FLOAT

#define __EFFECT_PRIVATE_NUMBER__ float

#else

#define __EFFECT_PRIVATE_NUMBER__ uint16_t

#endif

#define EFFECT_STATUS_OK 0x00
#define EFFECT_STATUS_ERROR 0x01

typedef struct
{
    uint32_t buffer_size;

    // Pointer that store address that point to first element of buffer
    __EFFECT_PRIVATE_NUMBER__ **input_buffer;
    __EFFECT_PRIVATE_NUMBER__ **output_buffer;

    uint32_t input_pointer;
    uint32_t output_pointer;

} Effect;

uint32_t effect_init(Effect *pEffect, uint32_t n_buffer);
void effect_deinit(Effect *pEffect);

void effect_update_input(Effect *pEffect, __EFFECT_PRIVATE_NUMBER__ input);
void effect_update_output(Effect *pEffect, __EFFECT_PRIVATE_NUMBER__ output);

__EFFECT_PRIVATE_NUMBER__ effect_get_input_sample(Effect *pEffect, uint32_t index);
__EFFECT_PRIVATE_NUMBER__ effect_get_output_sample(Effect *pEffect, uint32_t index);

#endif
