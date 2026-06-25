#pragma once
#include <cstdint>
/**
 * @brief Messages for Sensors
 *
 */
namespace fast::rf::messages::Sensor {
/**
 * @brief Data Structure for encoding GPS Data
 *
 */
struct GlobalPositionSensorData {
  double time_stamp;    //!< Timestamp of data
  double latitude_deg;  //!< Latitude in Degrees.  Range is [-90.0,90.0]
  double longitude_deg; //!< Longitude in Degrees.  Range is [-90.0, 90.0]
  double altitude_m;    //!< Altitude above sea level
  uint16_t satellites;  //!< Number of satellites used for data
  static inline constexpr double MAX_ANGLE =
      90.0; //!< Max Angle in degrees representing Geographic Coordinates
  static inline constexpr double MIN_ANGLE =
      -90.0; //!< Min Angle in degrees representing Geographic Coordinates

  GlobalPositionSensorData() {};
  /**
   * @brief Checks data to see if valid
   *
   * @return true Data is valid
   * @return false Data is not valid
   */
  bool ok() {
    if (latitude_deg > MAX_ANGLE) {
      return false;
    }
    if (latitude_deg < MIN_ANGLE) {
      return false;
    }
    if (longitude_deg > MAX_ANGLE) {
      return false;
    }
    if (longitude_deg < MIN_ANGLE) {
      return false;
    }
    return true;
  }
};
} // namespace fast::rf::messages::Sensor
