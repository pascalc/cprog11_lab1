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

static class TestDescription_MyTestSuite_testInitiateValueConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testInitiateValueConstructor() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 9, "testInitiateValueConstructor" ) {}
 void runTest() { suite_MyTestSuite.testInitiateValueConstructor(); }
} testDescription_MyTestSuite_testInitiateValueConstructor;

static class TestDescription_MyTestSuite_testInsertion : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testInsertion() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "testInsertion" ) {}
 void runTest() { suite_MyTestSuite.testInsertion(); }
} testDescription_MyTestSuite_testInsertion;

static class TestDescription_MyTestSuite_testPushBack : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testPushBack() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 45, "testPushBack" ) {}
 void runTest() { suite_MyTestSuite.testPushBack(); }
} testDescription_MyTestSuite_testPushBack;

static class TestDescription_MyTestSuite_testInsert : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testInsert() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 65, "testInsert" ) {}
 void runTest() { suite_MyTestSuite.testInsert(); }
} testDescription_MyTestSuite_testInsert;

static class TestDescription_MyTestSuite_testErase : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testErase() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 87, "testErase" ) {}
 void runTest() { suite_MyTestSuite.testErase(); }
} testDescription_MyTestSuite_testErase;

static class TestDescription_MyTestSuite_testNonConstAssignment : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testNonConstAssignment() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 114, "testNonConstAssignment" ) {}
 void runTest() { suite_MyTestSuite.testNonConstAssignment(); }
} testDescription_MyTestSuite_testNonConstAssignment;

static class TestDescription_MyTestSuite_testConst : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testConst() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 129, "testConst" ) {}
 void runTest() { suite_MyTestSuite.testConst(); }
} testDescription_MyTestSuite_testConst;

static class TestDescription_MyTestSuite_testSelfAssignment : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testSelfAssignment() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 137, "testSelfAssignment" ) {}
 void runTest() { suite_MyTestSuite.testSelfAssignment(); }
} testDescription_MyTestSuite_testSelfAssignment;

static class TestDescription_MyTestSuite_testExceptionOutOfRange : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_testExceptionOutOfRange() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 143, "testExceptionOutOfRange" ) {}
 void runTest() { suite_MyTestSuite.testExceptionOutOfRange(); }
} testDescription_MyTestSuite_testExceptionOutOfRange;

#include <cxxtest/Root.cpp>
