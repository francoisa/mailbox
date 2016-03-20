#ifndef TASK_H
#define TASK_H
#include <memory>

class PrimeNumberGenerator {
  public:
    PrimeNumberGenerator(int n) : number(n), done(false) { }

    bool is_done() const;
    long long do_work();
  private:
    int number;
    bool done;
};

bool ThereAreMoreTasks();

std::shared_ptr<PrimeNumberGenerator> AllocateAndBuildNewTask();

void DoWork(std::shared_ptr<PrimeNumberGenerator>& pg);
#endif
