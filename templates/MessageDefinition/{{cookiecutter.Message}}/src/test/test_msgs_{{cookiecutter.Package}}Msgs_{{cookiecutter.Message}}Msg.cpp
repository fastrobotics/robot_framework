
#include <{{cookiecutter.Message}}Msg.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::{{cookiecutter.Package}}Msgs;
TEST({{cookiecutter.Message}}Msg, DefaultZeroConstructor) {
  {{cookiecutter.Message}}Msg SUT;
  ASSERT_TRUE(false);
}