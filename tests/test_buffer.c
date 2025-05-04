#include "buffer.h"
#include "minunit.h"

MU_TEST(test_add) {

}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_add);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}

