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
    void test_constructor() {
        Vector<bool> v;
        TS_ASSERT(v.size() == 0);

        Vector<bool> w(31);
        TS_ASSERT(w.size() == 31);

        Vector<bool> x(0);
        TS_ASSERT(x.size() == 0);
    }

    void test_initialValueConstructor() {
        Vector<bool> v(32, true);
        check_equals(v);

        Vector<bool> w(31, false);
        check_equals(w, false);
    }

    void test_copyConstructor() {
        Vector<bool> v(15);
        Vector<bool> w(v);
        TS_ASSERT(w.size() == 15);
    }

    void test_copyAssignment() {
        Vector<bool> v(33, true);
        Vector<bool> w = v;
        TS_ASSERT(w.size() == 33);
        check_equals(w);
    }

    void test_selfAssignment() {
        Vector<bool> v(5, true);
        TS_ASSERT_EQUALS(v.size(), 5);
        check_equals(v, true);
        v = v;
        TS_ASSERT_EQUALS(v.size(), 5);
        check_equals(v, true);
    }

    void test_indexOutOfRange() {
        Vector<bool> v;
        TS_ASSERT_THROWS(v[0], std::out_of_range);
        TS_ASSERT_THROWS(v[31], std::out_of_range);
    }

    // const operator[] const
    void test_getIndexOperator() {
        Vector<bool> v(33, true);
        TS_ASSERT(v[0]);
        TS_ASSERT(v[15]);
        TS_ASSERT(v[16]);
        TS_ASSERT(v[31]);
        TS_ASSERT(v[32]);

        bool t = v[30];
        TS_ASSERT_EQUALS(t, v[30]);
        t = false;
        TS_ASSERT_EQUALS(v[30], true);

        TS_ASSERT_THROWS_ANYTHING(v[33]);
    }

    // operator[]
    void test_setIndexOperator() {
        Vector<bool> v(16);
        v[0] = true;
        v[15] = false;
        TS_ASSERT(v[0]);
        TS_ASSERT_EQUALS(v[15], false);

        bool t = v[10];
        TS_ASSERT_EQUALS(t, v[10]);
        t = false;
        v[11] = t;
        TS_ASSERT_EQUALS(v[11], false);

        TS_ASSERT_THROWS_ANYTHING(v[16] = false);
    }

    void test_bitAssignment() {
        TS_TRACE("Test setting of bit value");
        Vector<bool> v(4, true);
        v[0] = false;
        v[1] = false;
        v[2] = false;
        v[3] = false;
        TS_TRACE("true to false");
        check_equals(v, false);
        v[0] = true;
        v[1] = true;
        v[2] = true;
        v[3] = true;
        TS_TRACE("false to true");
        check_equals(v, true);
        TS_TRACE("End Test setting of bit value");
    }

    // test chaning of type v[0] = v[1] = ..
    void test_chainedAssignment() {
        Vector<bool> v(10);
        v[0] = v[1] = false;
        TS_ASSERT_EQUALS(v[0], false);
        TS_ASSERT_EQUALS(v[1], false);
    }

    void test_push_back() {
        Vector<bool> v;
        for(std::size_t i = 0; i < 1030; ++i) {
            v.push_back(true);
            TS_ASSERT(v[i]);
            TS_ASSERT(v.size() == (i+1));
        }
        check_equals(v);
    }

    void test_clear() {
        Vector<bool> v(15);
        TS_ASSERT(v.size() == 15);
        v.clear();
        TS_ASSERT(v.size() == 0);
        TS_ASSERT_THROWS_ANYTHING(v[0]);
    }

    void test_sort() {
        Vector<bool> empty;
        empty.sort();
        TS_ASSERT_EQUALS(empty.size(), 0)
        ;
        Vector<bool> one(1, true);
        one.sort();
        TS_ASSERT_EQUALS(one[0], true);
        one.sort(false);
        TS_ASSERT_EQUALS(one[0], true);
        TS_ASSERT_EQUALS(one.size(), 1);

        Vector<bool> two(2);
        two[0] = true;
        two[1] = false;
        two.sort();
        TS_ASSERT_EQUALS(two[0], false);
        TS_ASSERT_EQUALS(two[1], true);

        two.sort(false);
        TS_ASSERT_EQUALS(two[0], true);
        TS_ASSERT_EQUALS(two[1], false);

        Vector<bool> three(3);
        three[0] = true;
        three[1] = false;
        three[2] = true;
        three.sort();
        TS_ASSERT_EQUALS(three[0], false);
        TS_ASSERT_EQUALS(three[1], true);
        TS_ASSERT_EQUALS(three[2], true);

        three.sort(false);
        TS_ASSERT_EQUALS(three[0], true);
        TS_ASSERT_EQUALS(three[1], true);
        TS_ASSERT_EQUALS(three[2], false);


        Vector<bool> v(100, true);
        for(std::size_t i = 0; i < v.size(); ++i) {
            if(i % 2 == 0) v[i] = false;
        }
        v.sort();
        check_sorted(v);

        v.sort(false);
        check_sorted(v, false);

        v.sort(true);
        check_sorted(v, true);

        Vector<bool> vv(33, false);
        for(std::size_t i = 0; i < vv.size(); ++i) {
            if(i % 2 == 0) vv[i] = false;
        }
        vv.sort();
        check_sorted(vv);

        vv.sort(false);
        check_sorted(vv, false);

        vv.sort(true);
        check_sorted(vv, true);
    }

    void test_get_int() {
        Vector<bool> empty;
        TS_ASSERT_EQUALS(empty.get_int(), 0);

        Vector<bool> x(16, false);
        TS_ASSERT_EQUALS(x.get_int(), 0);

        Vector<bool> v(32);
        TS_ASSERT_EQUALS(v.get_int(), 0);
        v[0] = true;
        TS_ASSERT_EQUALS(v.get_int(), 1);
        v[2] = true;
        TS_ASSERT_EQUALS(v.get_int(), 5);
        v[3] = true;
        TS_ASSERT_EQUALS(v.get_int(), 13);
        v[0] = false;
        v[2] = false;
        v[3] = false;
        v[31] = true;
        TS_ASSERT_EQUALS(v.get_int(), 2147483648);

        Vector<bool> all(32, true);
        TS_ASSERT_EQUALS(all.get_int(), 0xFFFFFFFF);

        Vector<bool> over_size(33);
        TS_ASSERT_THROWS(over_size.get_int(), std::logic_error);
    }
};
