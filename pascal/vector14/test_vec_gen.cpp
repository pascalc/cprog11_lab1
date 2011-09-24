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
#include "test_vec.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_vec.cpp", 8, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_constructorOneArgument : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_constructorOneArgument() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "test_constructorOneArgument" ) {}
 void runTest() { suite_MyTestSuite.test_constructorOneArgument(); }
} testDescription_MyTestSuite_test_constructorOneArgument;

static class TestDescription_MyTestSuite_test_copyConstructorArgument : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_copyConstructorArgument() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 25, "test_copyConstructorArgument" ) {}
 void runTest() { suite_MyTestSuite.test_copyConstructorArgument(); }
} testDescription_MyTestSuite_test_copyConstructorArgument;

#include <cxxtest/Root.cpp>
