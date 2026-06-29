

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseUserInterfaceSystem.hpp>
#include <DummyUserInterfaceSystem/DummyUserInterfaceSystem.hpp>
#include <IUserInterfaceSystem.hpp>
// Test message types typically owned by System
TEST(MsgUserInterface, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::UserInterfaceSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IUserInterfaceSystem {
   public:
};
TEST(UserInterfaceSystemInterface, BasicAssertionsInterface) {
    TestConcreteSystemInterface SUT;
    ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseUserInterfaceSystem {
   public:
};
TEST(UserInterfaceSystemInterface, BasicAssertionsBaseClass) {
    TestConcreteSystemBase SUT;
    ASSERT_TRUE(true);
}

// System Basic Class Tests