

#include <IImplementControlSystem.hpp>

#include <BaseImplementControlSystem.hpp>

#include <DummyImplementControlSystem/DummyImplementControlSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgImplementControl, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::ImplementControlSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IImplementControlSystem {
public:
};
TEST(ImplementControlSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseImplementControlSystem {
public:
};
TEST(ImplementControlSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests