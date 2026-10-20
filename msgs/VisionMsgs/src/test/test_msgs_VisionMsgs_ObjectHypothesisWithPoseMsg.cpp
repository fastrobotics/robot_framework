
#include <gtest/gtest.h>
#include <stdio.h>

#include <ObjectHypothesisWithPoseMsg.hpp>
using namespace fast::rf::messages::VisionMsgs;
TEST(ObjectHypothesisWithPoseMsg, DefaultZeroConstructor) {
    ObjectHypothesisWithPoseMsg SUT;
    ASSERT_FALSE(SUT.isOk());
    ASSERT_GT(SUT.pretty().size(), 0);
    printf("%s\n", SUT.pretty().c_str());
}
TEST(ObjectHypothesisWithPoseMsg, ValidObjectHypothesis) {
    ObjectHypothesisWithPoseMsg SUT;
    SUT.score = 50.0;
    ASSERT_TRUE(SUT.isOk());
    printf("%s\n", SUT.pretty().c_str());

    // Test that Score is checked Ok
    auto invalidScoreObject = SUT;
    invalidScoreObject.score = -1.0;
    ASSERT_FALSE(invalidScoreObject.isOk());
    invalidScoreObject.score = 100.0 * 2.0;
    ASSERT_FALSE(invalidScoreObject.isOk());
}