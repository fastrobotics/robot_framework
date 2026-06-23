
#include "{{cookiecutter.Message}}Msg.hpp"

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::fr::messages;
TEST(Msg{Message}, DefaultZeroConstructor) {
  {{cookiecutter.Message}}Msg SUT;
  ASSERT_TRUE(false);
}
TEST(Msg{{cookiecutter.Message}}, DefaultConfigConstructor) {
}