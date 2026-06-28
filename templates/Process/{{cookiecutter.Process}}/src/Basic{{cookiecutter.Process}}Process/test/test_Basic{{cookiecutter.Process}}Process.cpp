

#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem;

TEST(Basic{{cookiecutter.Process}}Process, BasicTests) {
  Basic{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}
TEST(Basic{{cookiecutter.Process}}Process, BasicConversionTests) {
  Basic{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(true);
}