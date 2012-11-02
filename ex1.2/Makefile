# Change these
MATRIX_PATH = ../ex.1.1/
CCFLAGS = -std=c++0x -Wall

solver: maze_solver.cpp oMatrix.o
	g++ $(CCFLAGS) maze_solver.cpp oMatrix.o -o solver.out

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp
	
.cpp.o:
	g++ -Wall -Wextra -Weffc++ -g -c $< -o $@

oMatrix.o: oMatrix.h oMatrix.cpp

clean:
	-rm -f *.o *.out