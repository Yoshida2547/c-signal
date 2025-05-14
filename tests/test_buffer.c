#include "buffer.h"
#include "minunit.h"

MU_TEST(test_void_func) {
    int i = 91;

    int *i_ptr = &i;
    void *v_ptr = TO_VOID_P(i);

    // Check 1: Memory Address must be the same.
    mu_assert(i_ptr == v_ptr, "Memory Address must be the same.");

    // Check 2: Return value must be the same.
    int j = FROM_VOID(v_ptr, int);
    mu_assert(i == j, "Retun value must be the same.");
}

MU_TEST_SUITE(test_suit) {
    MU_RUN_TEST(test_void_func);
}

int main() {
    MU_RUN_SUITE(test_suit);
    MU_REPORT();
    return 0;
}