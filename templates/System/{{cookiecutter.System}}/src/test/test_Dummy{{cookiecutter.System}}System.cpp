
#include <Dummy{{cookiecutter.System}}System/Dummy{{cookiecutter.System}}System.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <gtest/gtest.h>
using namespace fast::rf::{{cookiecutter.System}}System;
TEST(Dummy{{cookiecutter.System}}System, BasicAssertions) {
  ASSERT_GT(fast::rf::{{cookiecutter.System}}System::SYSTEM_ID, 0);
  Dummy{{cookiecutter.System}}System SUT;
}