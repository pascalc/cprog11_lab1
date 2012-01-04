#include <iostream>
#include <stdexcept>
#include <cxxtest/TestSuite.h>

#include "bit_vector.h"     // inkludera din headerfil h�r

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
    void test_operatorsEmptyVectors() {
        Vector<bool> v, w;
        Vector<bool> and_(v & w);
        TS_ASSERT_EQUALS(and_.size(), 0);
        Vector<bool> or_(v | w);
        TS_ASSERT_EQUALS(or_.size(), 0);
        Vector<bool> xor_(v ^ w);
        TS_ASSERT_EQUALS(xor_.size(), 0);
    }

    void test_bitwise_and() {
        TS_TRACE("Testing operator&");
        Vector<bool> v(1, true), w(1, false);
        Vector<bool> a(v & w);
        TS_ASSERT_EQUALS(a[0], false);

        Vector<bool> three_1(3), three_2(3);
        three_1[0] = true;
        three_1[1] = false;
        three_1[2] = false;

        three_2[0] = true;
        three_2[1] = true;
        three_2[2] = false;

        Vector<bool> three_ans(three_1 & three_2);
        TS_ASSERT_EQUALS(three_ans[0], true);
        TS_ASSERT_EQUALS(three_ans[1], false);
        TS_ASSERT_EQUALS(three_ans[2], false);
    }

    void test_bitwise_or() {
        TS_TRACE("Testing operator|");
        Vector<bool> v(1, true), w(1, false);
        Vector<bool> a(v | w);
        TS_ASSERT_EQUALS(a[0], true);

        Vector<bool> three_1(3), three_2(3);
        three_1[0] = true;
        three_1[1] = false;
        three_1[2] = false;

        three_2[0] = true;
        three_2[1] = true;
        three_2[2] = false;

        Vector<bool> three_ans(three_1 | three_2);
        TS_ASSERT_EQUALS(three_ans[0], true);
        TS_ASSERT_EQUALS(three_ans[1], true);
        TS_ASSERT_EQUALS(three_ans[2], false);
    }

    void test_bitwise_xor() {
        TS_TRACE("Testing operator^");
        Vector<bool> v(1, true), w(1, false);
        Vector<bool> a(v ^ w);
        TS_ASSERT_EQUALS(a[0], true);

        Vector<bool> three_1(3), three_2(3);
        three_1[0] = true;
        three_1[1] = false;
        three_1[2] = false;

        three_2[0] = true;
        three_2[1] = true;
        three_2[2] = false;

        Vector<bool> three_ans(three_1 ^ three_2);
        TS_ASSERT_EQUALS(three_ans[0], true);
        TS_ASSERT_EQUALS(three_ans[1], false);
        TS_ASSERT_EQUALS(three_ans[2], true);
    }

};