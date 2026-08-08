/**
 * @file BaseLocalPoseFuserProcess.hpp
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

#include <ILocalPoseFuserProcess.hpp>
namespace fast::rf::PoseSystem::LocalPoseSubsystem {
/**
 * @brief Base LocalPoseFuser Process
  @details Concrete LocalPoseFuser Processes should derive from this
 *
 */
class BaseLocalPoseFuserProcess : public ILocalPoseFuserProcess {

public:
  /**
   * @brief Construct a new Base LocalPoseFuser Process object
   *
   */
  BaseLocalPoseFuserProcess() : diagnosticManager(fast::rf::PoseSystem::SYSTEM_ID,
                                fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                                fast::rf::PoseSystem::LocalPoseSubsystem::PROCESS_LOCALPOSEFUSER_ID),
                                 ready_to_arm(fast::rf::PoseSystem::SYSTEM_ID,
                                fast::rf::PoseSystem::LocalPoseSubsystem::SUBSYSTEM_ID,
                                fast::rf::PoseSystem::LocalPoseSubsystem::PROCESS_LOCALPOSEFUSER_ID)
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

        /**
         * @brief Pretty print the Process
         * 
         * @return std::string 
         */
    virtual std::string pretty();

protected:
  double current_time_sec_{-1.0};    //!< Current system time
  fast::rf::core::infrastructure::DiagnosticManager
            diagnosticManager;  //!< Entity responsible for managing diagnostics.
   fast::rf::messages::InfrastructureMsgs::ReadyToArmStatusMsg ready_to_arm;  //!< Ready to Arm object
};
} // namespace fast::rf::PoseSystem::LocalPoseSubsystem