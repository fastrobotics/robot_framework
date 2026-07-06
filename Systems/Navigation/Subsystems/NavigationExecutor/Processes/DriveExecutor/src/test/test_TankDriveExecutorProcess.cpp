
#include <gtest/gtest.h>

#include <RobotFrameworkDefinitions.hpp>
#include <TankDriveExecutorProcess/TankDriveExecutorProcess.hpp>

using namespace fast::rf::NavigationSystem::NavigationExecutorSubsystem;

TEST(TankDriveExecutorProcess, InitInitializesAndUpdatesDiagnostics) {
    TankDriveExecutorProcess SUT;

    // init() should initialize diagnostics and also perform the immediate updates
    ASSERT_TRUE(SUT.init());

    auto diagnostics = SUT.get_diagnostics();
    ASSERT_EQ(diagnostics.size(), 3);

    std::map<fast::rf::DiagnosticDefinition::DiagnosticType, fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
        diag_map;
    for (const auto& d : diagnostics) {
        diag_map.emplace(d.diagnosticType, d);
    }

    // SOFTWARE should be set to NOERROR / NOERROR with the SW Running description
    ASSERT_TRUE(diag_map.count(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE));
    auto sw = diag_map[fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE];
    ASSERT_EQ(sw.level, fast::rf::Level::NOERROR);
    ASSERT_EQ(sw.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR);
    ASSERT_EQ(sw.description, "SW Running.");

    // REMOTE_CONTROL should be WARN / NODATA
    ASSERT_TRUE(diag_map.count(fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL));
    auto rc = diag_map[fast::rf::DiagnosticDefinition::DiagnosticType::REMOTE_CONTROL];
    ASSERT_EQ(rc.level, fast::rf::Level::WARN);
    ASSERT_EQ(rc.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA);

    // ACTUATORS should be WARN / NODATA
    ASSERT_TRUE(diag_map.count(fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS));
    auto act = diag_map[fast::rf::DiagnosticDefinition::DiagnosticType::ACTUATORS];
    ASSERT_EQ(act.level, fast::rf::Level::WARN);
    ASSERT_EQ(act.diagnosticMessage, fast::rf::DiagnosticDefinition::DiagnosticMessage::NODATA);
}
