

#include <gtest/gtest.h>
#include <stdio.h>

#include <JoystickMapper.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
TEST(JoystickMapper, InterfaceTests) {
    JoystickMapper SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    auto mapped_joy = SUT.new_joy(joy);
    ASSERT_TRUE(mapped_joy.axes.size() == JoystickMapper::AXIS_COUNT);
}