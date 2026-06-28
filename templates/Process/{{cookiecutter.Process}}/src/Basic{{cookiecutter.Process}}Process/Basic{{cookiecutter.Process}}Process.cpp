#include <Basic{{cookiecutter.Process}}Process/Basic{{cookiecutter.Process}}Process.hpp>
namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem {
bool Basic{{cookiecutter.Process}}Process::update(double current_time_sec,
                                    double delta_time_sec) {
  bool status = Base{{cookiecutter.Process}}Process::base_update(current_time_sec, delta_time_sec);
  if (status == false) {
    return false;
  }
  return true;
}

} // namespace fast::rf::{{cookiecutter.System}}System::{{cookiecutter.Subsystem}}Subsystem