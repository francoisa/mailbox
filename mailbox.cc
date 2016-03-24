#include <vector>
#include <thread>
#include <iostream>
#include <memory>
#include "semaphore.h"
#include "mailbox.h"
#include "task.h"

using namespace std;

constexpr int K = 2;
vector<semaphore> sem(K);
vector<shared_ptr<PrimeNumberGenerator> > slot(K);

static auto done = make_shared<PrimeNumberGenerator>(0);

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
    cout << "Done producing" << endl;
    // Phase 2: Stuff the mailbox with done
    auto numNotified = 0;
    while (numNotified < K) {
        while (slot[curr] != nullptr)
            curr = (curr+1)%K;
        slot[curr] = done;
        sem[curr].notify();
        ++numNotified;
    }
    cout << "Number notified: " << numNotified << endl;
}

thread_local vector<long long> primes;

void consume(int mySlot) {
    shared_ptr<PrimeNumberGenerator> myTask = nullptr;
    while (myTask.get() != done.get()) {
        while ((myTask = slot[mySlot]) == nullptr)
            sem[mySlot].wait();
        if (myTask.get() != done.get()) {
            slot[mySlot] = nullptr;
            primes.push_back(DoWork(myTask));
        }
    }
    cout << "Size of primes vector: " << primes.size() << endl;
}
