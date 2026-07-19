#include <Base{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
bool Base{{cookiecutter.Process}}Process::base_update([[maybe_unused]] double current_time_sec) {

  current_time_sec_ = current_time_sec;

  return true;
}
std::string Base{{cookiecutter.Process}}Process::pretty() {

  std::string str = "\n---{{cookiecutter.Process}}---\n";
  str += "\tT: " + std::to_string(current_time_sec_) + "\n";

  str += diagnosticManager.pretty();

  return str;
}
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem