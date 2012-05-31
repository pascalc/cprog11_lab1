# default compile settings
CXX 	= g++
DEBUG	= -g
CFLAGS	= -Wall -Wextra -Weffc++ -c
LFLAGS	= -Wall

# cxxtest settings
CXXPATH	= ../../cxxtest/
CXXGEN 	= $(CXXPATH)cxxtestgen.py

tests: test_bit_vec test1_5 test1_6 test1_7

%.o: %.cpp
	$(CXX) $(DEBUG) $(CFLAGS) $*.cpp

# Dependencies
test_bit_vec.o:	test_bit_vec.cpp bit_vector.o
bit_vector.o:	bit_vector.h bit_vector.cpp

test1_%.cpp: test1_%.h
	python $(CXXGEN) --error-printer -o test1_$*.cpp test1_$*.h

test1_%: test1_%.cpp bit_vector.o
	$(CXX) -I $(CXXPATH) test1_$*.cpp -o test1_$*

test_bit_vec: test_bit_vec.o bit_vector.o
	$(CXX) $(DEBUG) $(LFLAGS) test_bit_vec.o bit_vector.o -o test_bit_vec

clean:
	rm -f *.o *~ test1_? test_bit_vec