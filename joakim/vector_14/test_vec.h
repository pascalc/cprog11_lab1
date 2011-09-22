#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>
#include "vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    
    // Testcase 1
    
    void test_constructor( void ) 
    {
        Vector a(7);           // initiering med 7 element
        TS_ASSERT_EQUALS(a.size, 7);
        TS_ASSERT_EQUALS(a[6], 0);
        
        Vector b(a);           // kopieringskonstruktor 
        TS_ASSERT_EQUALS(b.size, 7);    
        Vector c = a;          // kopieringskonstruktor
        TS_ASSERT_EQUALS(c.size, 7);
    }  
};
