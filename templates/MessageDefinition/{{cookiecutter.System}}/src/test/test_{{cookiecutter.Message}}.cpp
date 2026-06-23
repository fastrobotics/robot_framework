
#include "{{cookiecutter.Message}}Msg.hpp"

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages;
TEST(Msg{Message}, DefaultZeroConstructor) {
  {{cookiecutter.Message}}Msg SUT;
  ASSERT_TRUE(false);
}
TEST(Msg{{cookiecutter.Message}}, DefaultConfigConstructor) {
}