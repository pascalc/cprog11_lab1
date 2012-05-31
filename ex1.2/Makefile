# Change these
MATRIX_PATH = ../ex.1.1/

maze: maze.o oMatrix.o
	@echo "Matrix path set to " $(MATRIX_PATH)
	g++ -Wall maze.o oMatrix.o -o maze.out


%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp
	
.cpp.o:
	g++ -Wall -Wextra -Weffc++ -g -c $< -o $@

oMatrix.o: oMatrix.h oMatrix.cpp

clean:
	-rm -f *.o