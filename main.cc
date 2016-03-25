#include <thread>
#include "mailbox.h"

using namespace std;

class ThreadRAII {
  public:
    enum class DtorAction { join, detach };

    ThreadRAII(thread&& t, DtorAction a)  // in dtor, take action a on t
    : action(a), thrd(move(t)) {}

    ~ThreadRAII() {
        if (thrd.joinable()) {
            if (action == DtorAction::join) {
                thrd.join();
            }
            else {
                thrd.detach();
            }
        }
    }

    inline thread& get() { return thrd; }

  private:
    DtorAction action;
    thread thrd;
};

int main(int argc, char* argv[]) {
    // create a producer
    ThreadRAII p(thread(produce), ThreadRAII::DtorAction::detach);

    // create a consumer
    ThreadRAII c1(thread(consume, 0), ThreadRAII::DtorAction::join);
    ThreadRAII c2(thread(consume, 1), ThreadRAII::DtorAction::join);

    return 0;
}
