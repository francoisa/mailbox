TGT = mailbox
TST = $(TGT).t
OBJS =$(patsubst %.cc,.obj/%.o,$(filter-out $(TST).cc, $(wildcard *.cc)))
TSTOBJS =$(patsubst %.cc,.obj/%.o,$(filter-out main.cc, $(wildcard *.cc)))
CXX =g++
CC =g++
DEBUG =-g
CXXFLAGS = -Wall -std=gnu++0x -I. $(DEBUG) -pthread -lpthread -Wl,--no-as-needed
TESTLIBS = -lgtest

$(TGT): $(OBJS)
	$(LINK.cc) $^ $(LOADLIBS) $(LDLIBS) -o $@

$(TST): $(TSTOBJS)
	$(LINK.cc) $^ $(LOADLIBS) $(TESTLIBS) -o $@

.obj/%.o: %.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

main.o: main.cc $(TGT).h

$(TGT).o: $(TGT).cc $(TGT).h

task.o: task.cc task.h

semaphore.o: semaphore.cc semaphore.h

$(TST).o: $(TST).cc $(TGT).cc $(TGT).h

clean:
	rm -f .obj/*.o *~ $(TGT) $(TST)

test: $(TST)
	./$(TST)
