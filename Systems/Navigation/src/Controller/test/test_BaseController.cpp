#include <gtest/gtest.h>

#include <Controller/BaseController.hpp>
using namespace fast::rf::NavigationSystem::Controller;
class TestControllerConfig : public IControllerConfig {
   public:
    ~TestControllerConfig() override {}
    double test_config_attribute{0.0};
};
class TestControllerOutput : public IControllerOutput {
   public:
    ~TestControllerOutput() override {}
    double value{0.0};
};
class TestBaseController : public BaseController {
   public:
    bool init(IControllerConfig* config) {
        auto* config_ = dynamic_cast<TestControllerConfig*>(config);
        if (!config_) {
            return false;
        }
        if (config_->test_config_attribute > 0.0) {
            return false;
        }
        bool status = BaseController::init(config);
        output_ = new TestControllerOutput();
        return status;
    }
    bool new_set_point(double set_point, double time_stamp_sec) {
        return BaseController::new_set_point(set_point, time_stamp_sec);
    }
    bool new_sensor_input(double sensor_input, double time_stamp_sec) {
        return BaseController::new_sensor_input(sensor_input, time_stamp_sec);
    }
    bool update(double current_time_sec) {
        output_->value = 1.0;
        output_->is_new = true;
        return BaseController::update(current_time_sec);
    }
    TestControllerOutput* get_output() {
        TestControllerOutput* output = new TestControllerOutput(*output_);
        output_->is_new = false;

        return output;
    }
    std::string pretty() {
        auto config = dynamic_cast<TestControllerConfig*>(config_);
        std::string str = BaseController::pretty();
        str += "attr: " + std::to_string(config->test_config_attribute) + "\n";
        str += "val: " + std::to_string(output_->value) + "\n";
        return str;
    }

   private:
    TestControllerOutput* output_{nullptr};
};
TEST(BaseController, BasicAssertions) {
    TestBaseController SUT;
    IControllerConfig* config = new TestControllerConfig;
    ASSERT_TRUE(SUT.init(config));
    ASSERT_FLOAT_EQ(SUT.get_sensor_delta_time_sec(), -1.0);
    fast::rf::Logger::log_debug(SUT.pretty());
    double current_time_sec = 0.0;
    ASSERT_TRUE(SUT.new_set_point(0.0, current_time_sec));
    ASSERT_TRUE(SUT.new_sensor_input(0.0, current_time_sec));
    ASSERT_FLOAT_EQ(SUT.get_sensor_delta_time_sec(), -1.0);
    current_time_sec += 1.0;
    ASSERT_TRUE(SUT.update(current_time_sec));

    ASSERT_TRUE(SUT.new_sensor_input(0.0, current_time_sec));
    ASSERT_GT(SUT.get_sensor_delta_time_sec(), 0.0);
    auto output = SUT.get_output();
    ASSERT_NE(output, nullptr);
    ASSERT_FLOAT_EQ(output->value, 1.0);
    ASSERT_TRUE(output->is_new);
    output = SUT.get_output();
    ASSERT_FALSE(output->is_new);
    fast::rf::Logger::log_debug(SUT.pretty());
}