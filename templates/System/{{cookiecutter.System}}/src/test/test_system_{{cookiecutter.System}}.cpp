

#include <I{{cookiecutter.System}}System.hpp>

#include <Base{{cookiecutter.System}}System.hpp>

#include <Dummy{{cookiecutter.System}}System/Dummy{{cookiecutter.System}}System.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
// Test message types typically owned by System
TEST(Msg{{cookiecutter.System}}, NewMessages) { ASSERT_TRUE(true); }

using namespace fast::rf::{{cookiecutter.System}}System;
// System Interface Tests
class TestConcreteSystemInterface : public I{{cookiecutter.System}}System {
public:
};
TEST({{cookiecutter.System}}SystemInterface, BasicAssertionsInterface) {
  TestConcreteSystemInterface SUT;
  ASSERT_TRUE(true);
}

// System Base Class Tests
class TestConcreteSystemBase : public Base{{cookiecutter.System}}System {
public:
};
TEST({{cookiecutter.System}}SystemInterface, BasicAssertionsBaseClass) {
  TestConcreteSystemBase SUT;
  ASSERT_TRUE(true);
}

// System Basic Class Tests