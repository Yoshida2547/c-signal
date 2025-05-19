#include "buffer.h"
#include "minunit.h"

#include <math.h>

#define BUFFER_SIZE 16

buffer_t *buf;

void print_buffer();
void buffer_reset();

MU_TEST(test_buffer_init) {
    int ret = 0;

    ret = buffer_init(buf, BUFFER_SIZE, sizeof(float));
    mu_assert(!ret, "Fail to initialize buffer.");

    buffer_free(buf);

    ret = buffer_init(NULL, BUFFER_SIZE, sizeof(float));
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, 0, sizeof(float));
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, BUFFER_SIZE, 0);
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, BUFFER_SIZE, sizeof(float));
}

MU_TEST(test_buffer_set_get) {
    for(int i = 0; i < 16; i++) {
        float tmp = sinf(2*M_PI*i/16);

        buffer_set(buf, &tmp, i);
    }

    int fail = 0;

    for(int i = 0; i < 16; i++) {
        float tmp = 0;
        float test = sinf(2*M_PI*i/16);

        buffer_get(buf, &tmp, i);

        if(tmp != test) {
           fail += 1;
        }
    }

    mu_assert(fail == 0, "Fail to write to or read from.");
}

MU_TEST(test_buffer_set_get_byte) {
    for(uint32_t i = 0; i < buf->buffer_size; i++) {
        uint8_t tmp = i;

        buffer_set_byte(buf, &tmp, i);
    }

    int fail = 0;

    for(uint32_t i = 0; i < buf->buffer_size; i++) {
        uint8_t tmp = 0;
        uint8_t test = i;

        buffer_get_byte(buf, &tmp, i);

        if(tmp != test) {
            fail += 1;
        }
    }

    mu_assert(fail == 0, "Fail to write to or read from.");
}

MU_TEST(test_circular_push_pop) {
    buffer_reset();

    for(uint32_t i = 0; i < buf->buffer_size; i++) {
        float tmp = sinf(2*M_PI*i/15);
        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

    for(uint32_t i = 0; i < buf->buffer_size; i++) {
        float tmp = 0;
        float test = sinf(2*M_PI*i/15);

        circular_buf_pop(buf, &tmp);
        
        if(tmp != test) {
            fail += 1;
        }
    }

    mu_assert(fail == 0, "Fail to write to or read from.");
}

MU_TEST(test_circular_get_oldest) {

    buffer_reset();

    for(uint32_t i = 0; i < 28; i++) {
        float tmp = i;

        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

    float test[] = {12,13,14,15,16};

    for(int i = 0; i<5; i++) {
        float tmp = 0;

        circular_buf_get_oldest(buf, &tmp, i);

        if(test[i] != tmp) {
            fail += 1;
        }
    }

    mu_assert(fail == 0, "Fail to write to or read from.");
}

MU_TEST(test_circular_get_newest) {
    buffer_reset();

    for(uint32_t i = 0; i < 20; i++) {
        float tmp = i;

        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

    float test[] = {19,18,17,16,15};

    for(int i = 0; i<5; i++) {
        float tmp = 0;

        circular_buf_get_newest(buf, &tmp, i);

        if(test[i] != tmp) {
            fail += 1;
        }
    }

    mu_assert(fail == 0, "Fail to write to or read from.");
}

MU_TEST_SUITE(test_suit) {
    MU_RUN_TEST(test_buffer_init);
    MU_RUN_TEST(test_buffer_set_get);
    MU_RUN_TEST(test_buffer_set_get_byte);
    MU_RUN_TEST(test_circular_push_pop);

    MU_RUN_TEST(test_circular_get_oldest);
    MU_RUN_TEST(test_circular_get_newest);
}

void print_buffer() {
    printf("==================\r\n");
    for(uint32_t i = 0; i < 16; i++) {
        float tmp = 0;

        buffer_get(buf, &tmp, i);

        if(i == buf->head) {
            printf("H>%8.2f", tmp);
        } else {
            printf("%10.2f", tmp); 
        }

        if(i == buf->tail) {
            printf("    <T\r\n");
        } else {
            printf("\r\n");
        }
    }
    printf("==================\r\n");
}

void buffer_reset() {
    buffer_free(buf);

    buf =  (buffer_t *) malloc(sizeof(buffer_t));
    buffer_init(buf, BUFFER_SIZE, sizeof(float));
}

int main() {
    buf =  (buffer_t *) malloc(sizeof(buffer_t));

    MU_RUN_SUITE(test_suit);
    MU_REPORT();

    return 0;
}