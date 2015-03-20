CXX    = g++
FLAGS  = -O3 -std=c++11 -Wall -Wextra -Weffc++
EXE    = main.exe
DEPS   = makefile
SRCDIR = src
OBJDIR = obj
SRC_   = priority_queue.h\
	     sort.cpp\
	     sort_algorithm.cpp\
	     sort_algorithm.h
OBJ_   = sort.o\
	     sort_algorithm.o
SRC    = $(patsubst %,$(SRCDIR)/%,$(SRC_))
OBJ    = $(patsubst %,$(OBJDIR)/%,$(OBJ_))
###################################################


$(EXE):$(OBJ) $(SRC) $(DEPS)
	$(CXX) -o $(EXE) $(OBJ) $(FLAGS)
$(OBJDIR)/%.o:$(SRCDIR)/%.cpp  $(DEPS)
	$(CXX) -c $< -o $@ $(FLAGS)
.PHONY:clean

clean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(EXE)
	rm -rf $(EXE).exe

.PHONY:tidy

tidy:
	rm -rf $(OBJDIR)/*.o
