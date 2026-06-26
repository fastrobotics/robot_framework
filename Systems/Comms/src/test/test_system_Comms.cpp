

#include <ICommsSystem.hpp>

#include <BaseCommsSystem.hpp>

#include <DummyCommsSystem/DummyCommsSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgComms, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::CommsSystem;
// System Interface Tests
class TestConcreteSystemInterface : public ICommsSystem {
public:
};
TEST(CommsSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseCommsSystem {
public:
};
TEST(CommsSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests