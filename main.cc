#include <thread>
#include "mailbox.h"

using namespace std;

class ThreadRAII {
public:
  enum class DtorAction { join, detach };    // see Item 10 for
                                             // enum class info

  ThreadRAII(std::thread&& t, DtorAction a)  // in dtor, take
  : action(a), t(std::move(t)) {}            // action a on t

  ~ThreadRAII()
  {                                          // see below for
    if (t.joinable()) {                      // joinability test
      if (action == DtorAction::join) {
        t.join();
      } else {
        t.detach();
      }

    }
  }

  std::thread& get() { return t; }           // see below

private:
  DtorAction action;
  std::thread t;
};

int main(int argc, char* argv[]) {
    // create a consumer
    ThreadRAII c(thread(consume), ThreadRAII::DtorAction::join);
    // create a producer
    ThreadRAII c(thread(produce), ThreadRAII::DtorAction::detach);
    return 0;
}
