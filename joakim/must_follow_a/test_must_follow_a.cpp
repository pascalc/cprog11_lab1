#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 1

    // This testcase sets up a 5 sized array (precondition). Note that
    // the second argument (length) to must_follow_a is 4. The
    // expected result is successs.

    // Do make additional tests of your own and try it out. 

    void test_a_is_second_to_last( void )
    {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1);
    }

    // Testcase 2

    void test2( void ) 
    {
        char vek[] = {'a', 'a', 'b', 'b', 'b'};
        int result = must_follow_a(vek, 2, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
    }

    // Testcase 3

    // The assertion is what the function should return

    void test3( void ) 
    {
        char vek[] = {'b', 'b', 'a', 'b', 'b'};
        int result = must_follow_a(vek, 3, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
    }

    // Testcase 4

    // The assertion is what the function should return

    void test4( void )
    {
        char vek[] = {'x', 'x', 'x', 'x', 'a'};
        int result = must_follow_a(vek, 20, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
    }

     void test5( void ) 
    {
        char vek[] = {'b', 'a', 'b', 'b', 'b'};
        int result = must_follow_a(vek, 2, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
    }

};
