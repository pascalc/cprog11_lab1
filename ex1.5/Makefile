# Change these
CXXPATH	= ../../cxxtest/
CXXGEN 	= $(CXXPATH)cxxtestgen.py
T_CODE	= cxxtest_bit_vec.h

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp

testcode.cpp: $(T_CODE)
	python $(CXXGEN) --error-printer -o testcode.cpp $(T_CODE)

runourtest: testcode.cpp bit_vector.h
	g++ -I $(CXXPATH) -o runourtest testcode.cpp

test_bit_vec.o:	test_bit_vec.cpp bit_vector.h

test_bit_vec: test_bit_vec.o bit_vector.h
	g++ -g -Wall test_bit_vec.o bit_vector.h -o test_bit_vec

clean:
	rm -f *.o *.out testcode.cpp runourtest test_bit_vec

