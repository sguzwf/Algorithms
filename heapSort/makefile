EXE   = main
FLAGS = -std=c++11 -fpermissive -O3
$(EXE): heapsort.o
	g++ -o $(EXE) heapsort.o $(FLAGS)
	make tidy
heapsort.o:heapsort.cpp priority_queue.h
	g++ -c heapsort.cpp -o heapsort.o $(FLAGS)


.PHONY: tidy

tidy:
	rm -rf *.o

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf $(EXE)
