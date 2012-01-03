# Change these
CXXPATH	= ../../cxxtest/
CXXGEN 	= $(CXXPATH)cxxtestgen.py
T_CODE	= cxxtest_bit_vec.h
TEST_16 = cxxtest_ex1_6.h

%.o: %.cpp
	g++ -Wall -Wextra -Weffc++ -g -c $*.cpp

# Dependencies
test_bit_vec.o:	test_bit_vec.cpp bit_vector.h

testcode.cpp: $(T_CODE)
	python $(CXXGEN) --error-printer -o testcode.cpp $(T_CODE)

runourtest: testcode.cpp bit_vector.h
	g++ -I $(CXXPATH) -o runourtest testcode.cpp

testcode16.cpp: $(TEST_16)
	python $(CXXGEN) --error-printer -o testcode16.cpp $(TEST_16)

runttest_16: testcode16.cpp bit_vector.h
	g++ -I $(CXXPATH) -o runttest_16 testcode16.cpp

test_bit_vec: test_bit_vec.o bit_vector.h
	g++ -g -Wall test_bit_vec.o bit_vector.h -o test_bit_vec

clean:
	rm -f *.o *.out testcode.cpp runourtest test_bit_vec

