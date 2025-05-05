#include "buffer.h"
#include "minunit.h"

#include <stdint.h>

MU_TEST(test_pointer_next) {
    // Test next
    uint32_t ret; // Error handdle

    uint32_t buffer_size = 16;
    uint32_t pointer = 8;

    ret = circular_buffer_pointer_next(&pointer, buffer_size);

    mu_assert( pointer == 9, "pointer should moving to next position.");

    // Test end of buffer
    buffer_size = 16;
    pointer = 15;

    ret = circular_buffer_pointer_next(&pointer, buffer_size);

    mu_assert( pointer == 0, "pointer should moving to the begin of buffer.");

    // Test invalid input.

    // buffer_size zero
    buffer_size = 0;
    pointer = 15;

    ret = circular_buffer_pointer_next(&pointer, buffer_size);

    mu_assert(ret != 0, "Should return -1 if buffer size 0 input is passing.");

    // pointer outof length
    buffer_size = 16;
    pointer = 16;

    ret = circular_buffer_pointer_next(&pointer, buffer_size);

    mu_assert(ret != 0, "Should return -1 if pointer is outof length of buffer.");
}


MU_TEST(test_pointer_prev) {
    // Test next
    uint32_t ret; // Error handdle

    uint32_t buffer_size = 16;
    uint32_t pointer = 7;

    ret = circular_buffer_pointer_prev(&pointer, buffer_size);

    mu_assert(pointer == 6, "pointer should moving to previous position.");

    // Test end of buffer
    buffer_size = 16;
    pointer = 0;

    ret = circular_buffer_pointer_prev(&pointer, buffer_size);

    mu_assert(pointer == 15, "pointer should moving to the begin of buffer.");

    // Test invalid input.

    // buffer_size zero
    buffer_size = 0;
    pointer = 15;

    ret = circular_buffer_pointer_prev(&pointer, buffer_size);

    mu_assert(ret != 0, "Should return -1 if buffer size 0 input is passing.");

    // pointer outof length
    buffer_size = 14;
    pointer = 16;

    ret = circular_buffer_pointer_prev(&pointer, buffer_size);

    mu_assert(ret != 0, "Should return -1 if pointer is outof length of buffer.");
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_pointer_next);
    MU_RUN_TEST(test_pointer_prev);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}

