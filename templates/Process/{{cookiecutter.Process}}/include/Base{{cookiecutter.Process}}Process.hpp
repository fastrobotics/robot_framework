/**
 * @file Base{{cookiecutter.Process}}Process.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-27
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <Infrastructure/DiagnosticManager/DiagnosticManager.hpp>
#include <RobotFrameworkDefinitions.hpp>
#include <vector>

#include <I{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {
/**
 * @brief Base {{cookiecutter.Process}} Process
  @details Concrete {{cookiecutter.Process}} Processes should derive from this
 *
 */
class Base{{cookiecutter.Process}}Process : public I{{cookiecutter.Process}}Process {

public:
  /**
   * @brief Construct a new Base {{cookiecutter.Process}} Process object
   *
   */
  Base{{cookiecutter.Process}}Process() : diagnosticManager(fast::rf::{{cookiecutter.System}}System::SYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::SUBSYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}}::PROCESS_{{cookiecutter.Process_IDName}}_ID),
                                 ready_to_arm(fast::rf::{{cookiecutter.System}}System::SYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::SUBSYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}}::PROCESS_{{cookiecutter.Process_IDName}}_ID)
                                 {}
                  
  /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> getDiagnostics() override = 0;

         /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg getReadyToArm() override = 0; { return m_readyToArm; }

      protected:
       /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @return true
         * @return false
         */
        bool init() override = 0;
  
                                 /**
   * @brief Update the base object.  Called by Concrete Function.
   *
   * @param currentTimeSec
   * @return true If ok
   * @return false If not ok
   */
  bool update(double currentTimeSec) override = 0; //!< Base function to update
 
  /**
         * @brief Pretty print the Process.  Called by concrete object.
         * 
         * @return std::string 
         */
    std::string pretty() override = 0;
        double getCurrentTimeSec() { return m_currentTimeSec;}

    fast::rf::core::infrastructure::DiagnosticManager getDiagnosticManager() { return m_diagnosticManager;}  
  
    bool initializeDiagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types);

private:
  
  double m_currentTimeSec{-1.0};    //!< Current system time
  fast::rf::core::infrastructure::DiagnosticManager
            m_diagnosticManager;  //!< Entity responsible for managing diagnostics.
   fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg m_readyToArm;  //!< Ready to Arm object
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem