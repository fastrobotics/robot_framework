
#include <gtest/gtest.h>
#include <stdio.h>

#include <Detection3DMsg.hpp>
using namespace fast::rf::messages::VisionMsgs;
TEST(Detection3DMsg, DefaultZeroConstructor) {
    Detection3DMsg SUT;
    printf("%s\n", SUT.pretty().c_str());
}
TEST(Detection3DMsg, TestWithData) {
    Detection3DMsg SUT;
    for (uint8_t i = 0; i < 50; ++i) {
        ObjectHypothesisWithPoseMsg result;
        result.id = i;
        result.score = 5.0 + (i * 10.0);
        SUT.results.push_back(result);
    }
    ASSERT_GT(SUT.results.size(), 0);
    printf("%s\n", SUT.pretty().c_str());
}