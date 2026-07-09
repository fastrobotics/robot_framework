

#include <gtest/gtest.h>
#include <stdio.h>

#include <JoystickMapper.hpp>

using namespace fast::rf::UserInterfaceSystem::RemoteControlSubsystem;
TEST(JoystickMapper, InterfaceTests) {
    JoystickMapper SUT;
    fast::rf::messages::SensorMsgs::JoyMsg joy;
    for (uint8_t i = 0; i < JoystickMapper::AXIS_COUNT; ++i) {
        joy.axes.push_back((double)i);
    }
    // Add a few extra
    joy.axes.push_back(0.0);
    joy.axes.push_back(0.0);
    auto mapped_joy = SUT.new_joy(joy);
    ASSERT_TRUE(mapped_joy.axes.size() == JoystickMapper::AXIS_COUNT);
}