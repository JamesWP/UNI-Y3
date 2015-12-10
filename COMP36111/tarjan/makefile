BIN =./bin/
SOURCE=./source/
PROG = main
OBJS = main.o tarjan.o readgraph.o graph.o

$(PROG): $(OBJS)

main.o: tarjan.o tarjan.h
tarjan.o: readgraph.o
readgraph.o: graph.o

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(RUNTIME_PATH) $(OBJECTS) $(LIB_PATH) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(PROG) test/*.out

.PHONY: test
test: $(PROG) testTestOuts


TESTS=$(wildcard tests/*.out)
.PHONY: testTestOuts
testTestOuts: $(patsubst %.out,%.diff, $(TESTS))
	
%.diff:
	bash -c "diff $*.out <($(PROG) < $*)"

.PHONY: makeTestOuts
makeTestOuts: $(patsubst %,%.out,$(filter-out %.out, $(wildcard tests/*)))

tests/%.out: $(PROG)
	$(PROG) < tests/$* > tests/$*.out

