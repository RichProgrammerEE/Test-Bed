#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

#include <unistd.h>

using namespace std;

class Algorithm {
public:
    Algorithm(std::function<size_t()> algo) : _algo(algo) {
        std::cout << "Algorithm CTOR" << std::endl;
    }

    ~Algorithm() { std::cout << "Algorithm DTOR" << std::endl; }

    Algorithm(const Algorithm& rhs) {
        _algo = rhs._algo; // Is necessary, otherwise value never get initialized!
        std::cout << "Algorithm Copy CTOR" << std::endl;
    }

    size_t run() { return _algo(); }

private:
    std::function<size_t()> _algo;
};

class Processor {
public:
    Processor() {
        std::cout << "Processor CTOR" << std::endl;
        _run_thread = std::thread([this]() { runThread(); });
    }

    ~Processor() {
        std::cout << "Processor DTOR" << std::endl;
        {
            unique_lock<mutex> lock(_mtx);
            _done = true;
            _cond.notify_all();
        }

        _run_thread.join();
    }

    void addAlgorithm(const Algorithm& algo) {
        lock_guard<mutex> lock(_mtx);
        std::cout << "Adding Algorithm" << std::endl;
        _algo = std::make_shared<Algorithm>(algo);
        _update = true;
        _cond.notify_all();
    }

    void removeAlgorithm() {
        lock_guard<mutex> lock(_mtx);
        _algo.reset();
    }

    void runThread() {
        pthread_setname_np(pthread_self(), "processor");

        while(!_done) {
            std::cout << "Start of run loop" << std::endl;
            std::shared_ptr<Algorithm> algo;
            {
                unique_lock<mutex> lock(_mtx);
                if(!_update) {
                    _cond.wait(lock);
                    continue;
                }

                algo = _algo;
                _update = false;
            }

            std::cout << "Calling run" << std::endl;
            run(algo);
        }
    }

    void run(std::shared_ptr<Algorithm> algo) {
        auto result = algo->run();
        std::cout << "Sum: " << result << std::endl;
    }

private:
    std::shared_ptr<Algorithm> _algo;

    bool _update = false;
    std::mutex _mtx;
    std::condition_variable _cond;
    bool _done = false;
    std::thread _run_thread;
};

class Test {
public:
    Test() { std::cout << "Test CTOR" << std::endl; }

    ~Test() { std::cout << "Test DTOR" << std::endl; }

    Test(const Test& rhs) { std::cout << "Test Copy CTOR" << std::endl; }
};

int main() {
    auto p = new Processor();

    auto a = Algorithm([test = Test()]() -> size_t {
        size_t accum = 0;
        for(size_t i = 1; i <= 10000; i++) {
            accum += i;
        }
        return accum;
    });

    p->addAlgorithm(a);

    sleep(0.01);

    p->removeAlgorithm();

    return 0;
}