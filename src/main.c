#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "buffer.h"

buffer_t buf;

int main(void) {

    printf("Hello, World! 🌍\r\n");

    buffer_init(&buf, 16);

    for(int i = 0; i < 20; i++) {
        float tmp = i;

        circular_buf_push(&buf, &tmp);
    }

    buffer_print(&buf);

    for(int i = 0; i < 13; i++) {
        float tmp = 0;

        circular_buf_get_oldest(&buf, &tmp, i);

        printf("%f \r\n", tmp);
    }

    buffer_print(&buf);

    return 0;
}