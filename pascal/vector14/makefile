%.out:	%.cpp
	g++ -g -Wall $*.cpp -o $*.out

test_vec:
	g++ -c vector.cpp
	cxxtest/cxxtestgen.py --error-printer -o test_vec_gen.cpp test_vec.cpp
	g++ -o test_vec.out -I cxxtest/ test_vec_gen.cpp vector.o
