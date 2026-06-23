
#include "{{Message}}Msg.hpp"

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::fr::messages;
TEST(Msg{Message}, DefaultZeroConstructor) {
  {{Message}}Msg SUT;
  ASSERT_TRUE(false);
}
TEST(Msg{{Message}}, DefaultConfigConstructor) {
}