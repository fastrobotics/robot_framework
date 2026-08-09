#include <gtest/gtest.h>

#include <Controller/PIDController/PIDController.hpp>
using namespace fast::rf::NavigationSystem::Controller;

TEST(PIDController, BasicAssertions) {
    PIDController SUT;
    fast::rf::Logger::log_debug(SUT.pretty());
}