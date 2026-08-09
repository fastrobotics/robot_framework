#include <gtest/gtest.h>

#include <Controller/BaseController.hpp>
using namespace fast::rf::NavigationSystem::Controller;
class TestControllerConfig : public IControllerConfig {
   public:
    double test_attribute{1.0};
};
class TestBaseController : public BaseController {
   public:
    bool init(IControllerConfig* config) {
        bool status = BaseController::init(config);
        return status;
    }
    std::string pretty() {
        auto config = dynamic_cast<TestControllerConfig*>(config_);
        std::string str = BaseController::pretty();
        str += "attr: " + std::to_string(config->test_attribute) + "\n";
        return str;
    }
};
TEST(BaseController, BasicAssertions) {
    TestBaseController SUT;
    IControllerConfig* config = new TestControllerConfig;
    ASSERT_TRUE(SUT.init(config));
    fast::rf::Logger::log_debug(SUT.pretty());
}