#include <random>
#include <chrono>
#include "task.h"

using namespace std;
using namespace std::chrono;

static int get_rand() {
    static random_device r;

    static default_random_engine el(r());
    static uniform_int_distribution<int> uniform_dist(6, 26);

    return uniform_dist(el);
}

long long PrimeNumberGenerator::do_work() {
    long long prime = 2;
    int count = 0;
    while (count < number) {
        decltype(prime) d = 2;
        while (d < prime/2) {
            if (prime % d) {
                prime++;
                break;
            }
            else {
                d++;
            }
        }
        if (d >= prime/2 && prime % d) {
            count++;
        }
    }
    done = true;
    return prime;
}

bool PrimeNumberGenerator::is_done() const {
    return done;
}

bool ThereAreMoreTasks() {
    static auto start = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    return (30 < duration_cast<seconds>(now-start).count());
}

shared_ptr<PrimeNumberGenerator> AllocateAndBuildNewTask() {
    return make_shared<PrimeNumberGenerator>(PrimeNumberGenerator(get_rand()));
}

void DoWork(shared_ptr<PrimeNumberGenerator>& pg) {
    pg->do_work();
}
