CC = g++
FLAGS = -g -Wall
FILES = vector_14.cpp test_vec.cpp
OBJ = Vector_1.4.o test_vec.o
PROG = test_vec

%.out:	%.cpp
	g++ -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = cxxtest/cxxtest/
testcode    = 1.2b.cpp

$(PROG): $(OBJ)
	$(CC) -g -o $(PROG)  $(OBJ)

%.o: %.cpp
	$(CC) $(FLAGS) -c $*.cpp

test_vec.cpp: test_vec.cpp Vector_1.4.h
	$(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp 

clean:
	rm -f *.o

