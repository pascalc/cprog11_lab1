#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    void testInitiateValueConstructor( void ) 
    {
        Vector<int> a(7, 7);           // initiering med 7 element
        TS_ASSERT_EQUALS(a.size(), 7);
        for(size_t i = 0; i < a.size(); i++)
            TS_ASSERT_EQUALS(a[i], 7);
    }

    void testInsertion( void ) {
        Vector<double> d(10);
        TS_ASSERT_EQUALS(d.size(), 10);
        d.push_back(3.14);
        TS_ASSERT_EQUALS(d[10], 3.14);
        TS_ASSERT_EQUALS(d.size(), 11);
        d.insert(5, 2.78);
        TS_ASSERT_EQUALS(d.size(), 12);
        TS_ASSERT_EQUALS(d[5], 2.78);

        d.clear();
        TS_ASSERT_EQUALS(d.size(), 0);

        Vector<double> d1;
        d1.push_back(3.14);
        d1.push_back(2.78);
        // d1.push_back(4711);
        // d1.push_back(666.6);
        // TS_ASSERT_EQUALS(d1.size(), 4);
        // TS_ASSERT_EQUALS(d1[0], 3.14);
        // TS_ASSERT_EQUALS(d1[3], 666.6);
    }

    void testNonConstAssignment( void ) {
        Vector<long> a(7);
        a[5] = 7;            
        int i = a[5];
        a[5]++;
        TS_ASSERT_EQUALS(a[5], 8);
        TS_ASSERT_EQUALS(i , 7);

        a[4] = i;
        TS_ASSERT_EQUALS(a[4], 7);
        i--;
        TS_ASSERT_EQUALS(a[4], 7);

    }

    void testConst( void ) {
        const Vector<int> e(7);
        int i = e[5];
        //e[4] = i;   // Compile error = YES
        i++;
        TS_ASSERT_EQUALS(i, 1);
    }

    void testSelfAssignment( void ) {
        Vector<char> b;
        b = b;
        // How to test? valgrind?
    }

    void testExceptionOutOfRange( void ) {
        // How to test?
    }
};
