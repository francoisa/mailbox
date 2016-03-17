TGT = mailbox
TST = test/$(TGT).t
OBJS =$(patsubst %.cc,.obj/%.o,$(wildcard *.cc))
CXX =g++
CC =g++
DEBUG =-g
GTEST =../googletest/
CXXFLAGS = -Wall -std=gnu++0x -I. -I$(GTEST)/include $(DEBUG)
TESTLIBS = -L$(GTEST) -lgtest

$(TGT): $(OBJS)
	$(LINK.cc) $^ $(LOADLIBS) $(LDLIBS) -o $@

$(TST): .obj/$(TGT).o test/.obj/$(TGT).t.o
	$(LINK.cc) $^ $(LOADLIBS) $(TESTLIBS) -o $@

.obj/%.o: %.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

test/.obj/%.o: test/%.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

main.o: main.cc $(TGT).h

$(TGT).o: $(TGT).cc $(TGT).h

task.o: task.cc task.h

semaphore.o: semaphore.cc semaphore.h

$(TGT).t.o: $(TGT).t.cc. $(TGT).cc $(TGT).h

clean:
	rm -f .obj/*.o *~ $(TGT) test/.obj/*.o $(TST)

test: .obj/$(TGT).o test/.obj/$(TGT).t.o $(TST)
	$(TST)
