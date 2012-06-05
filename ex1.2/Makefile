# Change these
MATRIX_PATH = ../ex.1.1/

maze: maze_solver.o oMatrix.o
	g++ -Wall maze_solver.o oMatrix.o maze.cpp -o maze.out

maze_w: maze_working.cpp oMatrix.o
	g++ -Wall maze_working.cpp oMatrix.o -o maze_working.out

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp
	
.cpp.o:
	g++ -Wall -Wextra -Weffc++ -g -c $< -o $@

oMatrix.o: oMatrix.h oMatrix.cpp

maze_solver.o: maze_solver.h maze_solver.cpp

clean:
	-rm -f *.o