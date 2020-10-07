#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void incrementA(int* a)
{
    int tmp = *a;
    tmp = tmp + 1;
    *a = tmp;
}

void changeA(int* a)
{
    if(*a == -1)
        *a = 10;
}

int main()
{
    vector<size_t> results{ 0, 0, 0, 0};
    for(size_t i = 0; i < 10000; ++i) {
        int a = -1;
        std::thread second(changeA, &a);
        std::thread first(incrementA, &a);
        // synchronize threads:
        first.join();
        second.join();
        if(a == 0)
            results[0] += 1;
        else if(a == 10)
            results[1] += 1;
        else if(a == 11)
            results[2] += 1;
        else
            results[3] += 1;
    }

    cout << "Value of A:\n"
         << "0: " << results[0] << " times" << "\n"
         << "10: " << results[1] << " times" << "\n"
         << "11: " << results[2] << " times" << "\n"
         << "Unknown: " << results[3] << " times" << endl;

    return 0;
}