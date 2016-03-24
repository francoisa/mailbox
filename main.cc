#include <thread>
#include "mailbox.h"

using namespace std;

class ThreadRAII {
  public:
    enum class DtorAction { join, detach };

    ThreadRAII(thread&& t, DtorAction a)  // in dtor, take action a on t
    : action(a), thrd(std::move(t)) {}

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
    // create a consumer
    ThreadRAII c(thread(consume, 0), ThreadRAII::DtorAction::join);
    // create a producer
    ThreadRAII p(thread(produce), ThreadRAII::DtorAction::detach);
    c.get().join();

    return 0;
}
