#include <BasePoseSystem.hpp>
namespace fast::rf::PoseSystem {
bool BasePoseSystem::base_update(double current_time_sec,
                                 double delta_time_sec) {
  current_time_sec_ = current_time_sec;
  return true;
}

} // namespace fast::rf::PoseSystem