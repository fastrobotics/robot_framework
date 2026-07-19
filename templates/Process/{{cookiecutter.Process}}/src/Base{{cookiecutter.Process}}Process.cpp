#include <Base{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
bool Base{{cookiecutter.Process}}Process::update([[maybe_unused]] double current_time_sec) {

  current_time_sec_ = current_time_sec;
  if (diagnosticManager.get_diagnostics(fast::rf::Level::ERROR).size() == 0) {
      ready_to_arm.ready_to_arm = true;
  } else {
    ready_to_arm.ready_to_arm = false;
  }

  return true;
}
std::string Base{{cookiecutter.Process}}Process::pretty() {

  std::string str = "\n---{{cookiecutter.Process}}---\n";
  str += "\tT: " + std::to_string(current_time_sec_) + "\n";
   str += "\tReady To Arm: " + std::to_string(ready_to_arm.ready_to_arm) + "\n";
  str += diagnosticManager.pretty();

  return str;
}
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem