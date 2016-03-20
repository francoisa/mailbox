#include <vector>
#include <thread>
#include "semaphore.h"
#include "mailbox.h"
#include "task.h"

using namespace std;

constexpr int K = 2;
vector<semaphore> sem(K);
vector<shared_ptr<PrimeNumberGenerator> > slot(K);

static shared_ptr<PrimeNumberGenerator> done;

void produce() {
    auto curr = 0;
    // Phase 1: build and distribute tasks
    while (ThereAreMoreTasks()) {
        auto task = AllocateAndBuildNewTask();
        while (slot[curr] != nullptr)
            curr = (curr+1)%K;
        slot[curr] = task;
        sem[curr].notify();
    }
    // Phase 2: Stuff the mailbox with done
    auto numNotified = 0;
    while (numNotified < K) {
        while (slot[curr] != nullptr)
            curr = (curr+1)%K;
        slot[curr] = done;
        sem[curr].notify();
        ++numNotified;
    }
}


void consume(int mySlot) {
    shared_ptr<PrimeNumberGenerator> myTask = nullptr;
    while (myTask != done) {
        while ((myTask = slot[mySlot]) == nullptr)
            sem[mySlot].wait();
        if (myTask != done) {
            slot[mySlot] = nullptr;
            DoWork(myTask);
        }
    }
}
