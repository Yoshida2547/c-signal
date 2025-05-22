#include "buffer.h"
#include "minunit.h"

#include <math.h>

#define BUFFER_SIZE 16

buffer_t *buf;

void buffer_reset();

#ifdef __BUFFER_GENERIC__

void print_buffer();

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

#endif

void buffer_reset() {
    buffer_free(buf);

    buf =  (buffer_t *) malloc(sizeof(buffer_t));
#ifdef __BUFFER_GENERIC__
    buffer_init(buf, BUFFER_SIZE, sizeof(float));
#else
    buffer_init(buf, BUFFER_SIZE);
#endif
}

MU_TEST(test_buffer_init) {
    int ret = 0;

#ifdef __BUFFER_GENERIC__
    ret = buffer_init(buf, BUFFER_SIZE, sizeof(float));

    mu_assert(ret == 0, "Fail to initialize buffer.");

    buffer_free(buf);

    ret = buffer_init(NULL, BUFFER_SIZE, sizeof(float));
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, 0, sizeof(float));
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, BUFFER_SIZE, 0);
    mu_assert(ret,"Fail to handle invalid parameters.");

    if(ret) {
        ret = buffer_init(buf, BUFFER_SIZE, sizeof(float));
    }
#else
    ret = buffer_init(buf, BUFFER_SIZE);

    mu_assert(!ret, "Fail to initialize buffer.");

    buffer_free(buf);

    ret = buffer_init(NULL, BUFFER_SIZE);
    mu_assert(ret,"Fail to handle invalid parameters.");

    ret = buffer_init(buf, 0);
    mu_assert(ret,"Fail to handle invalid parameters.");

    if(ret) {
        ret = buffer_init(buf, BUFFER_SIZE);
    }
#endif
    
}

MU_TEST(test_buffer_set_get) {
    for(int i = 0; i < 16; i++) {

#ifdef __BUFFER_GENERIC__
        float tmp = sinf(2*M_PI*i/16);
#else
        BUFFER_DATATYPE tmp = (BUFFER_DATATYPE) sinf(2*M_PI*i/16);
#endif

        buffer_set(buf, &tmp, i);
    }

    int fail = 0;

    for(int i = 0; i < 16; i++) {
#ifdef __BUFFER_GENERIC__
        float tmp = 0;
        float test = sinf(2*M_PI*i/16);
#else
        BUFFER_DATATYPE tmp = 0;
        BUFFER_DATATYPE test = (BUFFER_DATATYPE) sinf(2*M_PI*i/16);
#endif

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
#ifdef __BUFFER_GENERIC__
        float tmp = sinf(2*M_PI*i/15);
#else
        BUFFER_DATATYPE tmp = (BUFFER_DATATYPE) 1000*sinf(2*M_PI*i/15);
#endif
        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

    for(uint32_t i = 0; i < buf->buffer_size; i++) {
#ifdef __BUFFER_GENERIC__
        float test = sinf(2*M_PI*i/15);
        float tmp = 0;
#else
        BUFFER_DATATYPE test = (BUFFER_DATATYPE) 1000*sinf(2*M_PI*i/15);
        BUFFER_DATATYPE tmp = 0;
#endif

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

#ifdef __BUFFER_GENERIC__
        float tmp = i;
#else
        BUFFER_DATATYPE tmp = i;
#endif

        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

#ifdef __BUFFER_GENERIC__
        float test[] = {12,13,14,15,16};
#else
        BUFFER_DATATYPE test[] = {12,13,14,15,16};
#endif

    for(int i = 0; i<5; i++) {
#ifdef __BUFFER_GENERIC__
        float tmp = i;
#else
        BUFFER_DATATYPE tmp = 0;
#endif

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
#ifdef __BUFFER_GENERIC__
        float tmp = i;
#else
        BUFFER_DATATYPE tmp = i;
#endif

        circular_buf_push(buf, &tmp);
    }

    int fail = 0;

#ifdef __BUFFER_GENERIC__
    float test[] = {4,19,18,17,16};
#else
    BUFFER_DATATYPE test[] = {4,19,18,17,16};
#endif

    for(int i = 0; i<5; i++) {

#ifdef __BUFFER_GENERIC__
        float tmp = 0;
#else
        BUFFER_DATATYPE tmp = 0;
#endif

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

int main() {
    buf =  (buffer_t *) malloc(sizeof(buffer_t));

    MU_RUN_SUITE(test_suit);
    MU_REPORT();

    return 0;
}