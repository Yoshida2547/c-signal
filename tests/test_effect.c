#include "minunit.h" 

MU_TEST_SUITE(test_suit) {

}

int main() {
    MU_RUN_SUITE(test_suit);
    MU_REPORT();
    return 0;
}