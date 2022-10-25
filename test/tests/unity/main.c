#include "unity.h"

#define NO_PROTECTION_MASK (1U << 0)
#define PROTECTION_MASK (1U << 1)

int flag = 0;

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_no_protection(void) {
  TEST_PASS_MESSAGE("no protection");
  // set the no-protection bit.
  // unity is expected to skip
  // this line because the test
  // has already passed.
  flag |= NO_PROTECTION_MASK;
}

void test_protection(void) {
  if (TEST_PROTECT()) {
    TEST_PASS_MESSAGE("protection");
  } else {
    // set the protection bit.
    // unity should loop back
    // to this line thanks to
    // the test protection
    // feature.
    flag |= PROTECTION_MASK;
  }
}

void test_final(void) {
  // check that the flag has the expected value
  // (showing the protection bit but not the no-protection bit)
  TEST_ASSERT_EQUAL_HEX(PROTECTION_MASK, flag);
}

// not needed when using generate_test_runner.rb
int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_no_protection);
  RUN_TEST(test_protection);
  RUN_TEST(test_final);
  return UNITY_END();
}
