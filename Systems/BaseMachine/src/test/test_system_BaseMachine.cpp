

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseBaseMachineSystem.hpp>
#include <DummyBaseMachineSystem/DummyBaseMachineSystem.hpp>
#include <IBaseMachineSystem.hpp>
// Test message types typically owned by System
TEST(MsgBaseMachine, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::BaseMachineSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IBaseMachineSystem {
   public:
};
TEST(BaseMachineSystemInterface, BasicAssertionsInterface) {
    TestConcreteSystemInterface SUT;
    ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseBaseMachineSystem {
   public:
};
TEST(BaseMachineSystemInterface, BasicAssertionsBaseClass) {
    TestConcreteSystemBase SUT;
    ASSERT_TRUE(true);
}

// System Basic Class Tests