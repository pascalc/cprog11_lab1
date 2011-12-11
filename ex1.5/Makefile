# Change these
cxxtestpath = ../../cxxtest/
testcode    = test_bool_vec.h

cpp.o:
	g++ -Wall -g -c $< -o $@

bool_vector.o = bool_vector.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runourtest: testcode.cpp bool_vector.o ../ex1.1/vector.h
	g++ -I $(cxxtestpath) -o runourtest testcode.cpp bool_vector.o

clean:
	rm -f testcode.cpp bool_vector.o

