#include <Base{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {
  bool Base{{cookiecutter.Process}}Process::init() {
    return true;
  }
  std::vector<fast::rf::messages::InfrastructureMsgs::DiagnosticMsg> Base{{cookiecutter.Process}}Process::getDiagnostics() {
            return diagnosticManager.get_diagnostics();
        }
bool Base{{cookiecutter.Process}}Process::update(double currentTimeSec) {

  mCurrentTimeSec = currentTimeSec;
  if (diagnosticManager.get_diagnostics(fast::rf::Level::ERROR).size() == 0) {
      readyToArm.ready_to_arm = true;
  } else {
    readyToArm.ready_to_arm = false;
  }

  return true;
}
bool Base{{cookiecutter.Process}}Process::initializeDiagnostics(std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes) {
   bool status = diagnosticManager.initialize_diagnostics(diagnosticTypes);
   return status;
}
std::string Base{{cookiecutter.Process}}Process::pretty() {

  std::string str = "\n---{{cookiecutter.Process}}---\n";
   str += "\tSys: " + std::string(fast::rf::{{cookiecutter.System}}System::toString(fast::rf::{{cookiecutter.System}}System::Id{})) + "/" +
               std::string(fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::toString(
                   fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::Id{})) +
               "/" +
               std::string(fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}}::toString(
                   fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}}::Id{})) +
               "\n";
  str += "\tT: " + std::to_string(m_currentTimeSec) + "\n";
   str += "\tReady To Arm: " + std::to_string(m_readyToArm.ready_to_arm) + "\n";
  str += m_diagnosticManager.pretty();

  return str;
}
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem