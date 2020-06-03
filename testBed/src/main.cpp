#include <iostream>
#include <thread>
#include <algorithm>

class Test {
    public:
    double x{ 0.0 };
};

int main() {
    // This makes more sense if you read this right to left
    Test * const test = new Test(); // Const Pointer
    Test const * test2 = new Test(); // Pointer to const object
    const Test * test3 = new Test(); // Pointer to const object
    test->x = 10;
    //test = test2;
    //test3->x = 10;

    delete test;
    delete test2;
    delete test3;

    std::cout << "Exiting main function!" << std::endl;
    return 0;
}