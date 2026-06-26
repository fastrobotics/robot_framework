

#include <INavigationSystem.hpp>

#include <BaseNavigationSystem.hpp>

#include <DummyNavigationSystem/DummyNavigationSystem.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(MsgNavigation, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::NavigationSystem;
// System Interface Tests
class TestConcreteSystemInterface : public INavigationSystem {
public:
};
TEST(NavigationSystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseNavigationSystem {
public:
};
TEST(NavigationSystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests