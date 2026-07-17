
#include <gtest/gtest.h>
#include <stdio.h>

#include <ArmStateChangeSrv.hpp>
using namespace fast::rf::messages::InfrastructureMsgs;
TEST(ArmStateChangeSrv, DefaultZeroConstructorRequest) {
    ArmStateChangeSrv::ArmStateChangeSrvRequest SUT;
    ASSERT_EQ(SUT.requested_armed_state, fast::rf::ArmedState::UNKNOWN);
}
TEST(ArmStateChangeSrv, DefaultZeroConstructorResponse) {
    ArmStateChangeSrv::ArmStateChangeSrvResponse SUT;
    ASSERT_EQ(SUT.current_armed_state, fast::rf::ArmedState::UNKNOWN);
    ASSERT_EQ(SUT.request_approved, false);
}
TEST(ArmStateChangeSrv, DefaultZeroConstructorService) {
    [[maybe_unused]] ArmStateChangeSrv SUT;
    ASSERT_TRUE(true);
}
class ServiceTester {
   public:
    ArmStateChangeSrv::ArmStateChangeSrvResponse do_it(ArmStateChangeSrv::ArmStateChangeSrvRequest request) {
        ArmStateChangeSrv::ArmStateChangeSrvResponse response;
        response.current_armed_state = request.requested_armed_state;
        response.request_approved = true;
        return response;
    }
};
TEST(ArmStateChangeSrv, ServiceTester) {
    ServiceTester SUT;
    ArmStateChangeSrv::ArmStateChangeSrvRequest request;
    request.requested_armed_state = fast::rf::ArmedState::ARMED;
    auto response = SUT.do_it(request);
    ASSERT_EQ(response.current_armed_state, request.requested_armed_state);
    ASSERT_TRUE(response.request_approved);
}