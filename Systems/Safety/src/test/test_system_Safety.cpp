

#include <ISafetySystem.hpp>

#include <BaseSafetySystem.hpp>

#include <DummySafetySystem/DummySafetySystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgSafety, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::SafetySystem;
// System Interface Tests
class TestConcreteSystemInterface : public ISafetySystem {
public:
};
TEST(SafetySystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseSafetySystem {
public:
};
TEST(SafetySystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests