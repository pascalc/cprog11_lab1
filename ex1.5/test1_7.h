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
        three_1[1] = true;
        three_1[2] = false;

        three_2[0] = false;
        three_2[1] = true;
        three_2[2] = false;

        Vector<bool> three_ans(three_1 & three_2);
        TS_ASSERT_EQUALS(three_ans[0], false);
        TS_ASSERT_EQUALS(three_ans[1], true);
        TS_ASSERT_EQUALS(three_ans[2], false);

        Vector<bool> big_1(127, false), big_2(127, false);
        
        for(uint index = 0; index < big_1.size(); ++index) {
            big_1[index] = true; big_2[index] = true;
            Vector<bool> big_ans(big_1 & big_2);
            TS_ASSERT_EQUALS(big_ans[index], true);
        }
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

        Vector<bool> big_1(127, false), big_2(127, false);
        
        for(std::size_t index = 0; index < big_1.size(); ++index) {
            big_1[index] = false; big_2[index] = true;
            Vector<bool> big_ans(big_1 | big_2);
            TS_ASSERT_EQUALS(big_ans[index], true);
        }
    }

    void test_bitwise_xor() {
        TS_TRACE("Testing operator^");
        Vector<bool> v(1, true), w(1, false);
        Vector<bool> a(v ^ w);
        TS_ASSERT_EQUALS(a[0], true);

        Vector<bool> two_1(2), two_2(2);
        two_1[0] = true;
        two_1[1] = false;
        two_2[0] = true;
        two_2[1] = false;
        Vector<bool> two_ans(two_1 ^ two_2);
        TS_ASSERT_EQUALS(two_ans[0], false);
        TS_ASSERT_EQUALS(two_ans[1], false);

        Vector<bool> three_1(3), three_2(3);
        three_1[0] = true;
        three_1[1] = false;
        three_1[2] = false;

        three_2[0] = true;
        three_2[1] = true;
        three_2[2] = false;

        Vector<bool> three_ans(three_1 ^ three_2);
        TS_ASSERT_EQUALS(three_ans[0], false);
        TS_ASSERT_EQUALS(three_ans[1], true);
        TS_ASSERT_EQUALS(three_ans[2], false);

        Vector<bool> big_1(127, false), big_2(127, true);
        
        for(uint index = 0; index < big_1.size(); ++index) {
            Vector<bool> big_ans(big_1 ^ big_2);
            TS_ASSERT_EQUALS(big_ans[index], true);
        }
    }

    void test_bitwise_invert() {
        Vector<bool> empty(0);
        ~empty;
        TS_ASSERT_EQUALS(empty.size(), 0);

        Vector<bool> one(1, true);
        ~one;
        TS_ASSERT_EQUALS(one[0], false);
        ~one;
        TS_ASSERT_EQUALS(one[0], true);

        Vector<bool> a(100, true);
        ~a;
        TS_ASSERT_EQUALS(a[0], false);
        TS_ASSERT_EQUALS(a[99], false);
    }

    void test_empty_weights() {
        Vector<bool> empty;
        TS_ASSERT_EQUALS(empty.weight1(), 0);
        TS_ASSERT_EQUALS(empty.weight2(), 0);
        TS_ASSERT_EQUALS(empty.weight3(), 0);
    }

    void test_weight1() {
        TS_TRACE("Testing count. First implementation");
        Vector<bool> a(50, true);
        TS_ASSERT_EQUALS(a.weight1(), 50);
        a[49] = false;
        TS_ASSERT_EQUALS(a.weight1(), 49);

        Vector<bool> b(32, false);
        TS_ASSERT_EQUALS(b.weight1(), 0);
        b[31] = true;
        TS_ASSERT_EQUALS(b.weight1(), 1);
    }

    void test_weight2() {
        TS_TRACE("Testing count. Second implementation");
        Vector<bool> a(50, true);
        TS_ASSERT_EQUALS(a.weight2(), 50);
        a[49] = false;
        TS_ASSERT_EQUALS(a.weight2(), 49);

        Vector<bool> b(32, false);
        TS_ASSERT_EQUALS(b.weight2(), 0);
        b[31] = true;
        TS_ASSERT_EQUALS(b.weight2(), 1);
    }

    void test_weight3() {
        TS_TRACE("Testing count. Second implementation");
        Vector<bool> a(50, true);
        TS_ASSERT_EQUALS(a.weight3(), 50);
        a[49] = false;
        TS_ASSERT_EQUALS(a.weight3(), 49);

        Vector<bool> b(32, false);
        TS_ASSERT_EQUALS(b.weight3(), 0);
        b[31] = true;
        TS_ASSERT_EQUALS(b.weight3(), 1);
    }

};
