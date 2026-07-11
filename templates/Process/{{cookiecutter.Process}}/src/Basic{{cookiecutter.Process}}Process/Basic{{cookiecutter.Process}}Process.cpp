#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {

bool Basic{{cookiecutter.Process}}Process::init() {
        std::vector<fast::rf::DiagnosticDefinition::DiagnosticType> diagnostic_types;
        diagnostic_types.push_back(fast::rf::DiagnosticDefinition::DiagnosticType::SOFTWARE);
        // Add more as needed
        bool status = diagnosticManager.initialize_diagnostics(diagnostic_types);
        return status;
    }
bool Basic{{cookiecutter.Process}}Process::update([[maybe_unused]]  double current_time_sec,
                                    [[maybe_unused]] double delta_time_sec) {
  bool status = Base{{cookiecutter.Process}}Process::base_update(current_time_sec, delta_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}

} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem