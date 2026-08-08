#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {

bool Basic{{cookiecutter.Process}}Process::init() {
  bool status = Base{{cookiecutter.Process}}Process::init();
  if(status == false) {
    return false;
  }
      std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
      diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
      // Add more as needed
      status = diagnosticManager.initialize_diagnostics(diagnostic_types);
      return status;
    }
bool Basic{{cookiecutter.Process}}Process::update(double current_time_sec) {
  bool status = Base{{cookiecutter.Process}}Process::update(current_time_sec);
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