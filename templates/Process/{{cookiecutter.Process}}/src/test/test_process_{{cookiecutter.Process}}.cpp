

#include <I{{cookiecutter.Process}}Process.hpp>

#include <Base{{cookiecutter.Process}}Process.hpp>

#include <gtest/gtest.h>
#include <stdio.h>

using namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem;
class Test{{cookiecutter.Process}}ProcessInterface : public I{{cookiecutter.Process}}Process {
public:
  bool init() { return true; }
  bool update([[maybe_unused]] double current_time_sec) override {
    return false;
  }
  std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> empty;

        return empty;
    }
  std::string pretty() override {
    return "";
  }
};
TEST(Test{{cookiecutter.Process}}ProcessInterface, InterfaceTests) {
  Test{{cookiecutter.Process}}ProcessInterface SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_EQ(SUT.get_diagnostics().size(), 0);
  ASSERT_FALSE(SUT.update(0.0));
}
class TestBase{{cookiecutter.Process}}Process : public Base{{cookiecutter.Process}}Process {
public:
  TestBase{{cookiecutter.Process}}Process() : Base{{cookiecutter.Process}}Process() {}
  bool init() override {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
  }
  bool update(double current_time_sec) override {
    return base_update(current_time_sec);
  }
};
TEST(Base{{cookiecutter.Process}}Process, BasicAssertions) {
  TestBase{{cookiecutter.Process}}Process SUT;
  ASSERT_TRUE(SUT.init());
  ASSERT_GT(SUT.get_diagnostics().size(), 0);
  ASSERT_TRUE(SUT.update(0.0));
}