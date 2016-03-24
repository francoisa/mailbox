#include <random>
#include <chrono>
#include <iostream>
#include "task.h"

using namespace std;
using namespace std::chrono;

static int get_rand() {
    static random_device r;

    static default_random_engine el(r());
    static uniform_int_distribution<int> uniform_dist(6, 26);

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
    static auto start = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    cout << "duration: " << duration_cast<seconds>(now-start).count() << endl;
    return (1 > duration_cast<seconds>(now-start).count());
}

shared_ptr<PrimeNumberGenerator> AllocateAndBuildNewTask() {
    return make_shared<PrimeNumberGenerator>(PrimeNumberGenerator(get_rand()));
}

long long DoWork(shared_ptr<PrimeNumberGenerator>& pg) {
    return pg->do_work();
}
