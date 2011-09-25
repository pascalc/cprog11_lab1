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
#include "test_vec.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test_vec.h", 6, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_testConstructors : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testConstructors() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 11, "testConstructors" ) {}
 void runTest() { suite_MyTestSuite.testConstructors(); }
} testDescription_MyTestSuite_testConstructors;

static class TestDescription_MyTestSuite_testNonConstAssignment : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testNonConstAssignment() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 27, "testNonConstAssignment" ) {}
 void runTest() { suite_MyTestSuite.testNonConstAssignment(); }
} testDescription_MyTestSuite_testNonConstAssignment;

static class TestDescription_MyTestSuite_testConst : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testConst() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 42, "testConst" ) {}
 void runTest() { suite_MyTestSuite.testConst(); }
} testDescription_MyTestSuite_testConst;

static class TestDescription_MyTestSuite_testSelfAssignment : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testSelfAssignment() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 50, "testSelfAssignment" ) {}
 void runTest() { suite_MyTestSuite.testSelfAssignment(); }
} testDescription_MyTestSuite_testSelfAssignment;

static class TestDescription_MyTestSuite_testExceptionOutOfRange : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testExceptionOutOfRange() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 56, "testExceptionOutOfRange" ) {}
 void runTest() { suite_MyTestSuite.testExceptionOutOfRange(); }
} testDescription_MyTestSuite_testExceptionOutOfRange;

#include <cxxtest/Root.cpp>
