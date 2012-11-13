# Change these
CXX_TEST_PATH = ../../cxxtest/
CXX_TEST_GEN = $(CXX_TEST_PATH)cxxtestgen.py
TESTCODE    = test_vec.h

%.out:	%.cpp
	g++ -g -Wall $*.cpp -o $*.out

testcode.cpp: $(TESTCODE)
	$(CXX_TEST_GEN) --error-printer -o testcode.cpp $(TESTCODE)

test.out: testcode.cpp test_vec.h vector.h
	g++ -o test.out -I $(CXX_TEST_PATH) testcode.cpp vector.h

clean:
	rm -f *.o ourtest testcode.cpp

vg-test.out:
	valgrind --tool=memcheck --leak-check=yes ./test.out
