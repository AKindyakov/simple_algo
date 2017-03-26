#include "../simple_algo_util/unit_test.h"

int EmptyFunction(int a, int b) {
    return a + b + 1;
}

int main() {
    TestSomeFunction(
        6,
        EmptyFunction,
        2, 3
    );
    return 0;
}

