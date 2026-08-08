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
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
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
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::PROCESS_{{cookiecutter.Process_IDName}}_ID),
                                 ready_to_arm(fast::rf::{{cookiecutter.System}}System::SYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::SUBSYSTEM_ID,
                                fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::PROCESS_{{cookiecutter.Process_IDName}}_ID)
                                 {}
  /**
         * @brief Initialize the base object.  Called by Concrete Function.
         *
         * @return true
         * @return false
         */
        virtual bool init();
  
                                 /**
   * @brief Update the base object.  Called by Concrete Function.
   *
   * @param current_time_sec
   * @return true If ok
   * @return false If not ok
   */
  virtual bool update(double current_time_sec); //!< Base function to update
                  
  /**
         * @brief Get the diagnostics object
         *
         * @return std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg>
         */
        std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> get_diagnostics() {
            return diagnosticManager.get_diagnostics();
        }

         /**
         * @brief Get the ready to arm object
         *
         * @return fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg
         */
        fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg get_ready_to_arm() override { return ready_to_arm; }

      

protected:
  /**
         * @brief Pretty print the Process
         * 
         * @return std::string 
         */
    virtual std::string pretty();
  double current_time_sec_{-1.0};    //!< Current system time
  fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
   fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
};
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem