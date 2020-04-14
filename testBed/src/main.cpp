#include <iostream>
#include <thread>
#include <algorithm>

void thread_function() {
    for(size_t i = 0; i < 100; ++i) {
        std::cout << "Thread (ID: " << std::this_thread::get_id();
        std::cout << ") function is executing!" << std::endl;
    }
}

class WorkerThread {
public:
    void operator()() {
        for(size_t i = 0; i < 10; ++i) {
            std::cout << "Thread (ID: " << std::this_thread::get_id();
            std::cout << ") functor override is executing!" << std::endl;
        }
    }
};

void newThreadCallback(int* p) {
    std::cout << "Inside Thread :  "
                 " : p = "
              << *p << std::endl;
    std::chrono::milliseconds dura(1000);
    std::this_thread::sleep_for(dura);
    *p = 19;
}

void startNewThread() {
    int i = 10;
    std::cout << "Inside Main Thread :  "
                 " : i = "
              << i << std::endl;
    std::thread t(newThreadCallback, &i);
    t.detach();
    std::cout << "Inside Main Thread :  "
                 " : i = "
              << i << std::endl;
}

int main() {
    // std::thread thread1(thread_function);
    // std::thread thread2((WorkerThread()));
    // std::thread thread3([]() {
    //     for(size_t i = 0; i < 10; ++i) {
    //         std::cout << "Thread (ID: " << std::this_thread::get_id();
    //         std::cout << ") with Lambda is executing!" << std::endl;
    //     }
    // });

    std::vector<std::thread> threadPool;
    for(size_t i = 0; i < 10; ++i)
        threadPool.push_back(std::thread((WorkerThread())));

    for(size_t i = 0; i < 10; ++i)
        std::cout << "Main thread is executing!" << std::endl;

    // Now wait for all the threads in the pool to finish by call
    // join() on each std::thread object
    std::for_each(threadPool.begin(), threadPool.end(), std::mem_fn(&std::thread::join));

    // //  This example write to memory that is no longer in scope!
    // startNewThread();
    // std::chrono::milliseconds dura( 2000 );
    // std::this_thread::sleep_for( dura );
    // return 0;

    std::cout << "Exiting main function!" << std::endl;
    return 0;
}