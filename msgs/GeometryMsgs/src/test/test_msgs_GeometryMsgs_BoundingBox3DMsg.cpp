
#include <gtest/gtest.h>
#include <stdio.h>

#include <BoundingBox3DMsg.hpp>
using namespace fast::rf::messages::GeometryMsgs;
TEST(BoundingBox3DMsg, DefaultZeroConstructor) {
    BoundingBox3DMsg SUT;
    ASSERT_GT(SUT.pretty().size(), 0);
}