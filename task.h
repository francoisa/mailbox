#ifndef TASK_H
#define TASK_H
#include <memory>

class PrimeNumberGenerator {
  public:
    PrimeNumberGenerator(int n) : number(n), done(false) { }

    bool is_done() const;
    long long do_work();
    inline int n() const { return number; }
  private:
    const int number;
    bool done;
};

bool ThereAreMoreTasks();

std::shared_ptr<PrimeNumberGenerator> AllocateAndBuildNewTask();

long long  DoWork(std::shared_ptr<PrimeNumberGenerator>& pg);
#endif
