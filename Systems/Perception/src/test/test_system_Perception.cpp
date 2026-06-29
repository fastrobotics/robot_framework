

#include <gtest/gtest.h>
#include <stdio.h>

#include <BasePerceptionSystem.hpp>
#include <DummyPerceptionSystem/DummyPerceptionSystem.hpp>
#include <IPerceptionSystem.hpp>
// Test message types typically owned by System
TEST(MsgPerception, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::PerceptionSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IPerceptionSystem {
   public:
};
TEST(PerceptionSystemInterface, BasicAssertionsInterface) {
    TestConcreteSystemInterface SUT;
    ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BasePerceptionSystem {
   public:
};
TEST(PerceptionSystemInterface, BasicAssertionsBaseClass) {
    TestConcreteSystemBase SUT;
    ASSERT_TRUE(true);
}

// System Basic Class Tests