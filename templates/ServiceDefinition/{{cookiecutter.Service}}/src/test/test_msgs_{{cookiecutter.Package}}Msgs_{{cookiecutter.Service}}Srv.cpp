
#include <{{cookiecutter.Service}}Srv.hpp>

#include <gtest/gtest.h>
#include <stdio.h>
using namespace fast::rf::messages::{{cookiecutter.Package}}Msgs;

TEST({{cookiecutter.Service}}Srv, DefaultZeroConstructorRequest) {
    {{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvRequest SUT;
    ASSERT_TRUE(false);
}
TEST({{cookiecutter.Service}}Srv, DefaultZeroConstructorResponse) {
    {{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvResponse SUT;
    ASSERT_TRUE(false);
}
TEST({{cookiecutter.Service}}Srv, DefaultZeroConstructorService) {
    {{cookiecutter.Service}}Srv SUT;
    ASSERT_TRUE(false);
}
class ServiceTester {
   public:
    {{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvResponse do_it({{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvRequest request) {
        {{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvResponse response;
        return response;
    }
};
TEST({{cookiecutter.Service}}Srv, ServiceTester) {
    ServiceTester SUT;
    {{cookiecutter.Service}}Srv::{{cookiecutter.Service}}SrvRequest request;
    auto response = SUT.do_it(request);
    ASSERT_TRUE(false);
}