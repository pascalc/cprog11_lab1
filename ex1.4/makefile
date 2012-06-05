test:
	g++ hypercube.h test_hypercube.cpp -o test_hypercube.out

# hypercube: hypercube.o vector.o
#	g++ -Wall hypercube.o vector.o -o hypercube.out

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp
	
.cpp.o:
	g++ -Wall -Wextra -Weffc++ -g -c $< -o $@

#vector.o: vector.h vector.cpp
hypercube.o: hypercube.h hypercube.cpp

clean:
	-rm -f *.o