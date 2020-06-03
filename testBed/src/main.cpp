#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <condition_variable>

bool is_ready{ false };
std::mutex m;
std::condition_variable cv;

void func()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_lock<std::mutex> lk(m);
    is_ready = true;
    cv.notify_one();
}

int main() {
    std::thread t(func);
    std::unique_lock<std::mutex> lk(m);
    while(!is_ready) {
        cv.wait(lk);
        if(!is_ready)
            std::cout << "Spurious wake up!\n";
    }
    t.join();
    std::cout << "Exiting main function!" << std::endl;
    return 0;
}