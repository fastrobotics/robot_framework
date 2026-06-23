
#include <{{cookiecutter.Message}}Msg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::fr::messages;
TEST(MsgPose, DefaultZeroConstructor) {
  {{cookiecutter.Message}}Msg SUT;
  ASSERT_TRUE(false);
}
