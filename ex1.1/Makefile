# Change these
cxxtestpath = ../../cxxtest/
testcode    = example_test.h

oMatrix.o = oMatrix.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: 
	g++ -c Matrix.h
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)
	g++ -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o

clean:
	touch runtest01 testcode.cpp
	rm -f runtest0* testcode.cpp *.o

