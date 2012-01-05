# Change these
CXXPATH	= ../../cxxtest/
CXXGEN 	= $(CXXPATH)cxxtestgen.py
T_CODE	= cxxtest_bit_vec.h
TEST_16 = cxxtest_ex1_6.h

tests: test_bit_vec test1_5 test1_6 test1_7

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp

# Dependencies
test_bit_vec.o:	test_bit_vec.cpp bit_vector.h

test1_%.cpp: test1_%.h
	python $(CXXGEN) --error-printer -o test1_$*.cpp test1_$*.h

test1_%: test1_%.cpp bit_vector.h
	g++ -I $(CXXPATH) -o test1_$*.out test1_$*.cpp

test_bit_vec: test_bit_vec.o bit_vector.h
	g++ -g -Wall test_bit_vec.o bit_vector.h -o test_bit_vec.out

clean:
	rm -f *.o *.out