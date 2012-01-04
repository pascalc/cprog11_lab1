#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "bit_vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
private:
    void check_equals(Vector<bool>& v, bool value = true) {
        for(std::size_t i = 0; i < v.size(); ++i)
            TS_ASSERT_EQUALS(v[i], value);
    }

    void check_sorted(Vector<bool>& v, bool ascending = true) {
        for(std::size_t i = 0; i < v.size() - 1; ++i) {
            if(ascending) {
                TS_ASSERT_LESS_THAN_EQUALS(v[i], v[i+1]);
            }
            else {
                TS_ASSERT_LESS_THAN_EQUALS(v[i+1], v[i]);
            }
        }
    }

public:
    /** const_iterator tests **/
    void test_cit_constructor() {
        Vector<bool> v;
        Vector<bool>::const_iterator it = v.begin();
        Vector<bool>::const_iterator end = v.end();
    }

    void test_cit_copy_constructor() {
        Vector<bool> v;
        Vector<bool>::const_iterator it = v.begin();
        Vector<bool>::const_iterator it2(it);
        Vector<bool>::const_iterator it3 = it2;

        TS_ASSERT_EQUALS(it, it2);
        TS_ASSERT_EQUALS(it2, it3);
    }

    void test_cit_dereference() {
        Vector<bool> v(10, true);
        Vector<bool>::const_iterator it = v.begin();
        for(; it != v.end(); ++it)
            TS_ASSERT_EQUALS( *it, true);
    }

    void test_cit_difference() {
        Vector<bool> empty_one, empty_two;
        Vector<bool>::const_iterator it_one = empty_two.begin(), it_two = empty_two.begin();
        TS_ASSERT_EQUALS(it_one - it_two, 0);

        Vector<bool> v(30, true), w(25, false);
        Vector<bool>::const_iterator it_v = v.begin(), it_w = w.begin();
        TS_ASSERT_EQUALS(it_v - it_w, 5);
    }


};
