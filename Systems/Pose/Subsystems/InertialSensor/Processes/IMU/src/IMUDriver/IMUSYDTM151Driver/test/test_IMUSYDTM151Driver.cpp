

#include <gtest/gtest.h>
#include <stdio.h>

#include <IMUDriver/IMUSYDTM151Driver/IMUSYDTM151Driver.hpp>
#include <Infrastructure/Logger.hpp>

using namespace fast::rf::PoseSystem::InertialSensorSubsystem;

TEST(IMUSYDTM151Driver, InterfaceTests) {
    IMUSYDTM151Driver SUT;
    ASSERT_TRUE(SUT.init());
    fast::rf::Logger::log_info(SUT.pretty());
}