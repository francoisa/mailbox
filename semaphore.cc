#include "semaphore.h"

void semaphore::notify() {
    unique_lock<mutex> lck(mtx);
    ++count;
    cv.notify_one();
}

void semaphore::wait() {
    unique_lock<mutex> lck(mtx);
    while (count == 0) {
        cv.wait(lck);
    }
    --count;
}
