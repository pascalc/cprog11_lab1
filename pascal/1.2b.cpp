/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_must_follow_a.cpp", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "test_a_is_second_to_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last(); }
} testDescription_MyTestSuite_test_a_is_second_to_last;

static class TestDescription_MyTestSuite_test_a_is_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 24, "test_a_is_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_last(); }
} testDescription_MyTestSuite_test_a_is_last;

static class TestDescription_MyTestSuite_test_tuple : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_tuple() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 31, "test_tuple" ) {}
 void runTest() { suite_MyTestSuite.test_tuple(); }
} testDescription_MyTestSuite_test_tuple;

#include <cxxtest/Root.cpp>
