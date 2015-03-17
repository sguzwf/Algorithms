EXE = main
$(EXE): priority heapsort
	g++ -o $(EXE) heapsort.o priority_queue.o -std=c++11
	make tidy
priority:priority_queue.cpp priority_queue.h
	g++ -c priority_queue.cpp -o priority_queue.o -std=c++11
heapsort:heapsort.cpp priority_queue.h
	g++ -c heapsort.cpp -o heapsort.o -std=c++11


.PHONY: tidy

tidy:
	rm -rf *.o

.PHONY: clean

clean:
	rm -rf *.o
	rm -rf $(EXE)
