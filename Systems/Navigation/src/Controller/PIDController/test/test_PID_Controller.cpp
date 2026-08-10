#include <gtest/gtest.h>

#include <Controller/PIDController/PIDController.hpp>
#include <fstream>
#include <iostream>
using namespace fast::rf::NavigationSystem::Controller;
#include <cmath>
#include <limits>
TEST(PIDController, BasicAssertions) {
    PIDController SUT;
    IControllerConfig* config = new PIDControllerConfig;
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
    ASSERT_TRUE(output->is_new);
    output = SUT.get_output();
    ASSERT_FALSE(output->is_new);
    fast::rf::Logger::log_debug(SUT.pretty());
}
TEST(PIDController, SimpleCompute) {
    PIDController SUT;
    IControllerConfig* config = new PIDControllerConfig;
    config->set_parameters(5.0, -5.0);
    auto* config_ = dynamic_cast<PIDControllerConfig*>(config);
    ASSERT_FALSE(config_ == nullptr);
    config_->set_parameters(2.0, 0.0, 0.0, 2.0);
    ASSERT_TRUE(SUT.init(config));
    double current_time_sec = 0.0;
    ASSERT_TRUE(SUT.new_set_point(1.0, current_time_sec));
    ASSERT_TRUE(SUT.new_sensor_input(0.2, current_time_sec));
    fast::rf::Logger::log_debug(SUT.pretty());
    auto output = SUT.get_output();
    ASSERT_TRUE(output->is_new);
    ASSERT_FLOAT_EQ(output->P_term, 1.2);
    ASSERT_FLOAT_EQ(output->I_term, 0.0);
    ASSERT_FLOAT_EQ(output->D_term, 0.0);
    ASSERT_FLOAT_EQ(output->setpoint_sensor_error, 0.6);
    ASSERT_FLOAT_EQ(output->command_value, 1.2);
}
struct TestDataRecord {
    double time_stamp;
    double set_point;
    double sensor_value;
    double expected_command_value;
    double expected_setpoint_sensor_error;
    double expected_p_term;
    double expected_i_term;
    double expected_d_term;
};
TestDataRecord parse(std::vector<std::string> items) {
    TestDataRecord record;
    record.time_stamp = std::stod(items[0]);
    record.set_point = std::stod(items[1]);
    record.sensor_value = std::stod(items[2]);
    record.expected_command_value = std::stod(items[3]);
    record.expected_setpoint_sensor_error = std::stod(items[6]);
    record.expected_p_term = std::stod(items[7]);
    record.expected_i_term = std::stod(items[8]);
    record.expected_d_term = std::stod(items[9]);
    return record;
}
TEST(PIDController, DataReadProcess) {
    std::string data_path = std::string(TEST_DATA_DIR) + "/PIDController_testdata_StepSetPoint.csv";
    std::ifstream file(data_path);
    ASSERT_TRUE(file.is_open());
    std::vector<std::vector<std::string>> data_rows;
    std::string line;
    // Read the file line by line
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        // Split the line using the comma delimiter
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data_rows.push_back(row);
    }
    file.close();
    ASSERT_FALSE(file.is_open());
    // Parse the CSV
    std::string name = "";
    double dt = INFINITY;
    double sensor_scale_value = INFINITY;
    double max_command_value = INFINITY;
    double min_command_value = INFINITY;
    double K_P = INFINITY;
    double K_I = INFINITY;
    double K_D = INFINITY;

    bool process_meta_data = true;
    bool process_test_data = false;
    std::vector<TestDataRecord> test_data_records;
    for (auto entry : data_rows) {
        if (entry.size() == 0) {
            continue;
        }
        if (entry[0] == "Time Stamp") {
            process_meta_data = false;
            process_test_data = true;
            continue;
        }
        // Step 1: Get the Meta Data
        if (process_meta_data == true) {
            if (entry[0] == "Name") {
                name = entry[1];
            } else if (entry[0] == "dT") {
                dt = std::stod(entry[1]);
            } else if (entry[0] == "Sensor Scale Value") {
                sensor_scale_value = std::stod(entry[1]);
            } else if (entry[0] == "Max Command Value") {
                max_command_value = std::stod(entry[1]);
            } else if (entry[0] == "Min Command Value") {
                min_command_value = std::stod(entry[1]);
            } else if (entry[0] == "K_P") {
                K_P = std::stod(entry[1]);
            } else if (entry[0] == "K_I") {
                K_I = std::stod(entry[1]);
            } else if (entry[0] == "K_D") {
                K_D = std::stod(entry[1]);
            }
        }

        // Step 2: Parse the Test Data
        if (process_test_data == true) {
            ASSERT_EQ(entry.size(), 15);
            auto record = parse(entry);
            test_data_records.push_back(record);
        }
    }
    ASSERT_NE(name, "");
    ASSERT_NE(dt, INFINITY);
    ASSERT_NE(sensor_scale_value, INFINITY);
    ASSERT_NE(max_command_value, INFINITY);
    ASSERT_NE(min_command_value, INFINITY);
    ASSERT_NE(K_P, INFINITY);
    ASSERT_NE(K_I, INFINITY);
    ASSERT_NE(K_D, INFINITY);

    ASSERT_GT(test_data_records.size(), 0);

    PIDController SUT;
    IControllerConfig* config = new PIDControllerConfig;
    config->set_parameters(max_command_value, min_command_value);
    auto* config_ = dynamic_cast<PIDControllerConfig*>(config);
    ASSERT_FALSE(config_ == nullptr);
    config_->set_parameters(K_P, K_I, K_D, sensor_scale_value);
    ASSERT_TRUE(SUT.init(config));
    for (auto test_data_record : test_data_records) {
        ASSERT_TRUE(SUT.new_set_point(test_data_record.set_point, test_data_record.time_stamp));
        ASSERT_TRUE(SUT.new_sensor_input(test_data_record.sensor_value, test_data_record.time_stamp));

        auto output = SUT.get_output();
        ASSERT_TRUE(output->is_new);
        ASSERT_FLOAT_EQ(output->setpoint_sensor_error, test_data_record.expected_setpoint_sensor_error);
        ASSERT_FLOAT_EQ(output->P_term, test_data_record.expected_p_term);
        ASSERT_FLOAT_EQ(output->I_term, test_data_record.expected_i_term);
        ASSERT_FLOAT_EQ(output->D_term, test_data_record.expected_d_term);
        ASSERT_FLOAT_EQ(output->command_value, test_data_record.expected_command_value);
    }
}