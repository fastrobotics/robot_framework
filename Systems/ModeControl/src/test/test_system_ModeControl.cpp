

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseModeControlSystem.hpp>
#include <DummyModeControlSystem/DummyModeControlSystem.hpp>
#include <IModeControlSystem.hpp>
// Test message types typically owned by System
TEST(MsgModeControl, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::ModeControlSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IModeControlSystem {
   public:
};
TEST(ModeControlSystemInterface, BasicAssertionsInterface) {
    TestConcreteSystemInterface SUT;
    ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseModeControlSystem {
   public:
};
TEST(ModeControlSystemInterface, BasicAssertionsBaseClass) {
    TestConcreteSystemBase SUT;
    ASSERT_TRUE(true);
}

// System Basic Class Tests