#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "bit_vector.h"     // inkludera din headerfil här

class MyTestSuite : public CxxTest::TestSuite 
{
private:
    typedef Vector<bool>::const_iterator cit;

    void check_equals(Vector<bool>& v, bool value = true) {
        cit it = v.begin();
        for(; it != v.end(); ++it)
            TS_ASSERT_EQUALS(*it, value);
    }

public:
    /** const_iterator tests **/
    void test_constructor() {
        Vector<bool> v;
        Vector<bool>::const_iterator it = v.begin();
        Vector<bool>::const_iterator end = v.end();
    }

    void test_copy_constructor() {
        Vector<bool> v;
        Vector<bool>::const_iterator it = v.begin();
        Vector<bool>::const_iterator it2(it);
        Vector<bool>::const_iterator it3 = it2;

        TS_ASSERT_EQUALS(it, it2);
        TS_ASSERT_EQUALS(it2, it3);
    }

    void test_dereference() {
        Vector<bool> v(10, true);
        Vector<bool>::const_iterator it = v.begin();
        TS_TRACE("Testing operator*");
        TS_ASSERT_EQUALS( *it, true);
    }

    void test_addition() {
        Vector<bool> v(10, true);
        Vector<bool>::const_iterator it = v.begin();

        TS_TRACE("Testing postfix operator++()");
        for(; it != v.end(); it++)
            TS_ASSERT_EQUALS(*it, true);

        Vector<bool> w(10, false);
        Vector<bool>::const_iterator it_w = w.begin();
        TS_TRACE("Testing prefix operator++(int)");
        for(; it_w != w.end(); ++it_w)
            TS_ASSERT_EQUALS(*it_w, false);

        TS_TRACE("Testing operator+=(size_t)");
        Vector<bool> a(10, true);
        a[5] = false;
        cit it_a = a.begin();
        it_a += 5;
        TS_ASSERT_EQUALS(*it_a, false);
    }

    void test_subtraction() {
        Vector<bool> v(10, true);
        Vector<bool>::const_iterator it = v.begin();
        std::advance(it, v.size()-1);

        TS_TRACE("Testing postfix operator--()");
        for(; it != v.end(); it--)
            TS_ASSERT_EQUALS(*it, true);

        Vector<bool> w(10, false);
        Vector<bool>::const_iterator it_w = w.begin();
        std::advance(it_w, w.size()-1);
        TS_TRACE("Testing prefix operator--(int)");
        for(; it_w != w.end(); --it_w)
            TS_ASSERT_EQUALS(*it_w, false);

        TS_TRACE("Testing operator-=(size_t)");
        Vector<bool> a(10, true);
        a[4] = false;
        cit it_a = a.begin();
        std::advance(it_a, 9);
        it_a -= 5;
        TS_ASSERT_EQUALS(*it_a, false);
    }

    void test_iterator_difference() {
        Vector<bool> empty_one, empty_two;
        Vector<bool>::const_iterator it_one = empty_two.begin(), it_two = empty_two.begin();
        TS_ASSERT_EQUALS(it_one - it_two, 0);

        Vector<bool> a(10), b(5);
        Vector<bool>::const_iterator it_a = a.begin(), it_b = b.begin();
        std::advance(it_a, 5);
        TS_ASSERT_EQUALS(it_a - it_b, 5);
    }


};
