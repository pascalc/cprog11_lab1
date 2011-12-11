# Change these
cxxtestpath = ../../cxxtest/
testcode    = example_test.h

cpp.o:
	g++ -Wall -g -c $< -o $@

oMatrix.o = oMatrix.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: 
	g++ -c Matrix.h
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)
	g++ -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o

runourtest: testcode.cpp oMatrix.o vector.h
	g++ -I $(cxxtestpath) -o runourtest testcode.cpp oMatrix.o

clean:
	touch runtest01 testcode.cpp
	rm -f runtest0* testcode.cpp oMatrix.o

