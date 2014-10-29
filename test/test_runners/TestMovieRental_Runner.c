#include "unity.h"
#include <setjmp.h>
#include <stdio.h> 

extern void setUp(void);
extern void tearDown(void);

extern void test_Customer_Statement_Should_Be_Correct(void);

static void runTest(UnityTestFunction test) {
  if (TEST_PROTECT()) {
    setUp();
    test();
  }

  if (TEST_PROTECT() && !TEST_IS_IGNORED) {
    tearDown();
  }
}

void resetTest() {
  tearDown();
  setUp();
}

int main(void) {
  Unity.TestFile = "test/TestMovieRental.c";
  UnityBegin();

  // RUN_TEST calls runTest
  RUN_TEST(test_Customer_Statement_Should_Be_Correct, 14);

  UnityEnd();
  return 0;
}
