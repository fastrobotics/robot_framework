

#include <I{{cookiecutter.Process}}Process.hpp>

#include <Base{{cookiecutter.Process}}Process.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem;
class Test{{cookiecutter.Process}}ProcessInterface : public I{{cookiecutter.Process}}Process {
public:
  bool update(double current_time_sec, double delta_time_sec) override {
    return false;
  }
};
TEST(Test{{cookiecutter.Process}}ProcessInterface, InterfaceTests) {
  Test{{cookiecutter.Process}}ProcessInterface SUT;
  ASSERT_FALSE(SUT.update(0.0, 0.0));
}
class TestBase{{cookiecutter.Process}}Process : public Base{{cookiecutter.Process}}Process {
public:
  TestBase{{cookiecutter.Process}}Process() : Base{{cookiecutter.Process}}Process() {}

  bool update(double current_time_sec, double delta_time_sec) override {
    return base_update(current_time_sec, delta_time_sec);
  }
};
TEST(Base{{cookiecutter.Process}}Process, BasicAssertions) {
  TestBase{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(SUT.update(0.0, 0.0));
}