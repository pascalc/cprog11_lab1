#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "bool_vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
public:
    void testInitiateValueConstructor( void ) 
    {
        Vector<bool> v(32, true);
        for(std::size_t i = 0; i < v.size(); ++i)
            TS_ASSERT(v[i]);

        Vector<bool> w(31, false);
        for(std::size_t i = 0; i < w.size(); ++i)
            TS_ASSERT( !w[i] );    
    }

    void testPushBack( void ) {
        Vector<bool> v;
        v.push_back(true);
        TS_ASSERT(v.size() == 1);
        TS_ASSERT( v[0] );
        
        v.push_back(false);
        TS_ASSERT(v.size() = 2);
        TS_ASSERT( !v[1] );
        
        Vector<bool> w(31, true);
        w.push_back( false );
        for(std::size_t i = 0; i < w.size() - 1; ++i)
            TS_ASSERT( w[i] );
        TS_ASSERT( !w[w.size()-1] );
    }

    void testClear( void ) {
        Vector<bool> v(15);
        TS_ASSERT(v.size() == 15);
        v.clear();
        TS_ASSERT(v.size() == 0);
    }

    void testOutOfRange( void ) {
        Vector<bool> v(31);
        try {
            bool test = v[31];
        } catch(std::out_of_range ) {}
        
        v.push_back(true);
        bool test = v[31];

        try {
            bool test = v[32];
        } catch(std::out_of_range ) {}
    }

    #if 0
    void testConst( void ) {
        const Vector<bool> v(7);
        bool i = v[5];   
        v[6] = false;   // Compile error = ?
    }
    

    void testSelfAssignment( void ) {
        Vector<bool> b;
        b = b;      // memory leakage?
    }
    #endif
};
