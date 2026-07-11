
#include <gtest/gtest.h>

#include <DummyBaseMachineSystem/DummyBaseMachineSystem.hpp>
#include <RobotFrameworkDefinitions.hpp>
using namespace fast::rf::BaseMachineSystem;
TEST(DummyBaseMachineSystem, BasicAssertions) {
    ASSERT_GT(fast::rf::BaseMachineSystem::SYSTEM_ID, 0);
    DummyBaseMachineSystem SUT;
}