/**
 * @compare_tag Process-BasicSource v0.1
 * 
 */
#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem::{{cookiecutter.Process}} {

bool Basic{{cookiecutter.Process}}Process::init() {
  bool status = Base{{cookiecutter.Process}}Process::init();
  if(status == false) {
    return false;
  }
      std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnosticTypes;
      diagnosticTypes.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
      // Add more as needed
     status = m_diagnosticManager.initializeDiagnostics(diagnosticTypes);
      return status;
    }
bool Basic{{cookiecutter.Process}}Process::update(double currentTimeSec) {
  bool status = Base{{cookiecutter.Process}}Process::update(currentTimeSec);
  if (status == false) {
    return false;
  }
  return true;
}
std::string Basic{{cookiecutter.Process}}Process::pretty() {
    std::string str = "---Basic {{cookiecutter.Process}} Process---";
    str += Base{{cookiecutter.Process}}Process::pretty();
    return str;
}

} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem
