

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseNavigationSystem.hpp>
#include <DummyNavigationSystem/DummyNavigationSystem.hpp>
#include <INavigationSystem.hpp>
#include <RobotFrameworkDefinitions.hpp>

// Test message types typically owned by System
TEST(MsgNavigation, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::NavigationSystem;
// System Interface Tests
class TestConcreteSystemInterface : public INavigationSystem {
   public:
};
TEST(NavigationSystemInterface, BasicAssertionsInterface) {
    ASSERT_GT(fast::rf::NavigationSystem::SYSTEM_ID, 0);
    ASSERT_GT(fast::rf::NavigationSystem::GlobalPlannerSubsystem::SUBSYSTEM_ID, 0);
    ASSERT_GT(fast::rf::NavigationSystem::LocalPlannerSubsystem::SUBSYSTEM_ID, 0);
    ASSERT_GT(fast::rf::NavigationSystem::NavigationExecutorSubsystem::SUBSYSTEM_ID, 0);
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