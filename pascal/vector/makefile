%.out:	%.cpp
	g++ -g -Wall $*.cpp -o $*.out

must_follow_a_tests:
	g++ -c must_follow_a.cpp
	cxxtest/cxxtestgen.py --error-printer -o 1.2b.cpp test_must_follow_a.cpp
	g++ -o test_1.2b.out -I cxxtest/ 1.2b.cpp must_follow_a.o
