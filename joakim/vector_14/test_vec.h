#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    // Testcase 1

    void testConstructors( void ) 
    {
        Vector a(7);           // initiering med 7 element
        TS_ASSERT_EQUALS(a.size(), 7);
        TS_ASSERT_EQUALS(a[6], 0);
        
        Vector b(a);           // kopieringskonstruktor 
        TS_ASSERT_EQUALS(b.size(), 7);    
        Vector c = a;          // kopieringskonstruktor
        TS_ASSERT_EQUALS(c.size(), 7);

        a[0] = 5;
        TS_ASSERT_EQUALS(c[0], 0);
        
    }

    void testNonConstAssignment( void ) {
        Vector a(7);
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
        const Vector e(7);
        int i = e[5];
        //e[4] = i;   // Compile error = YES
        i++;
        TS_ASSERT_EQUALS(i, 1);
    }

    void testSelfAssignment( void ) {
        Vector b;
        b = b;
        // How to test? valgrind?
    }

    void testExceptionOutOfRange( void ) {
        // How to test?
        const Vector e(7);
        int i;
        try {
            i = e[10];
        } catch (std::out_of_range e) {
            std::cout << e.what() << std::endl;
        }

        try {
            i = e[-1];
        } catch (std::out_of_range e) {
            std::cout << e.what() << std::endl;
        }
    }
};
