#include <random>
#include <chrono>
#include <iostream>
#include "task.h"

using namespace std;
using namespace std::chrono;

static int get_rand() {
    static random_device r;

    static default_random_engine el(r());
    static uniform_int_distribution<int> uniform_dist(6, 10000);

    return uniform_dist(el);
}

long long nextPrimeCandidate(long long candidate) {
    if (candidate == 1 || candidate == 2) {
        candidate++;
    }
    else {
        candidate += 2;
    }
    return candidate;
}

long long PrimeNumberGenerator::do_work() {
    long long prime = 1;
    int count = 0;
    while (count < number) {
        prime = nextPrimeCandidate(prime);
        decltype(prime) d = 3;
        while (d < prime/2) {
            if (!(prime % d)) {
                break;
            }
            else {
                d += 2;
            }
        }
        if (prime == d) {
            count++;
        }
        else if (d >= prime/2 && prime % d) {
            count++;
        }
    }
    done = true;
    return prime;
}

bool PrimeNumberGenerator::is_done() const {
    return done;
}

bool operator==(const PrimeNumberGenerator& lhs,
                const PrimeNumberGenerator& rhs) {
    return lhs.n() == rhs.n();
}

bool operator!=(const PrimeNumberGenerator& lhs,
                const PrimeNumberGenerator& rhs) {
    return lhs.n() != rhs.n();
}

bool ThereAreMoreTasks() {
    static auto count = 0;
    count++;
    return (count < 100);
}

PrimeNumberGenerator* AllocateAndBuildNewTask() {
    return new PrimeNumberGenerator(get_rand());
}

long long DoWork(PrimeNumberGenerator* pg) {
    auto result = pg->do_work();
    delete pg;
    return result;
}
