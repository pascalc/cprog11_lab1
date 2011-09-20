CC = g++
FLAGS = -g -Wall
OBJ = Vector_1.4.o test_vec.o
PROG = test_vec

%.out:	%.cpp
	g++ -g -Wall $*.cpp -o $*.out

# Change these
cxxtestpath = cxxtest/cxxtest/
testcode    = 1.2b.cpp

#$(PROG): $(OBJ)
#	$(CC) -g -o $(PROG)  $(OBJ)

#%.o: %.cpp
#	$(CC) $(FLAGS) -c $*.cpp

#testcode.cpp: $(testcode)
#	$(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

#clean:
#	rm -f *.o $(PROG) test_vec.cpp

