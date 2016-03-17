#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <mutex>
#include <condition_variable>
using namespace std;

class semaphore {
public:
    semaphore(int count_ = 0) : count{count_} {}
    semaphore(const semaphore& s) =delete;

    void notify();
    void wait();

private:

    mutex mtx;
    condition_variable cv;
    int count;
};
#endif
