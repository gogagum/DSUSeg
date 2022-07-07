#include <iostream>

extern "C" {
    void fake_sum(int a, int b) { std::cout <<  a + b + 1 << std::endl; }
}
