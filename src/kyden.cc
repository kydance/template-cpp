#include "kyden.h"

int my_func(int a) {
    std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl;
    std::cout << a << std::endl;
    return 0;
}