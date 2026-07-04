

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseCommsSystem.hpp>
#include <DummyCommsSystem/DummyCommsSystem.hpp>
#include <ICommsSystem.hpp>
#include <RobotFrameworkDefinitions.hpp>
// Test message types typically owned by System
TEST(MsgComms, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::CommsSystem;
// System Interface Tests
class TestConcreteSystemInterface : public ICommsSystem {
   public:
};
TEST(CommsSystemInterface, BasicAssertionsInterface) {
    ASSERT_GT(fast::rf::CommsSystem::SYSTEM_ID, 0);
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