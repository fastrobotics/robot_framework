#include <Base{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
bool Base{{cookiecutter.Process}}Process::base_update(double current_time_sec,
                                        double delta_time_sec) {

  current_time_sec_ = current_time_sec;

  return true;
}
} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem