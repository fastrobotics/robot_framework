

#include <gtest/gtest.h>
#include <stdio.h>

#include <BaseGoalPlanningSystem.hpp>
#include <DummyGoalPlanningSystem/DummyGoalPlanningSystem.hpp>
#include <IGoalPlanningSystem.hpp>
// Test message types typically owned by System
TEST(MsgGoalPlanning, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::GoalPlanningSystem;
// System Interface Tests
class TestConcreteSystemInterface : public IGoalPlanningSystem {
   public:
};
TEST(GoalPlanningSystemInterface, BasicAssertionsInterface) {
    TestConcreteSystemInterface SUT;
    ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public BaseGoalPlanningSystem {
   public:
};
TEST(GoalPlanningSystemInterface, BasicAssertionsBaseClass) {
    TestConcreteSystemBase SUT;
    ASSERT_TRUE(true);
}

// System Basic Class Tests