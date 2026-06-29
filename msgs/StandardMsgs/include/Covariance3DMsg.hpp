/**
 * @file Covariance3DMsg.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-06-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <cstdint>
#include <vector>
namespace fast::rf::messages::StandardMsgs {
/**
* @brief 3D Covariance
 @details
 Row-major representation of the 6x6 covariance matrix
 The orientation parameters use a fixed-axis representation.
 In order, the parameters are: (X1,X2,X3,X4,X5,X6)

Diagonal elemnts are treated as follows:
>0: Valid Covariance
0: Undefined/Not Supported
<0: Unknown Covariance.
*
*/
struct Covariance3DMsg {
    static inline constexpr uint16_t DIMENSION = 3;  //!< Dimensionality of Covariance.
    static inline constexpr uint16_t X1 = 0;         //!< Diagonal Element Index
    static inline constexpr uint16_t X2 = 4;         //!< Diagonal Element Index
    static inline constexpr uint16_t X3 = 8;         //!< Diagonal Element Index
    std::vector<double> covariance;                  //!< Covariance data
    Covariance3DMsg() {
        covariance.resize(DIMENSION * DIMENSION);
        covariance[X1] = -1.0;
        covariance[X2] = -1.0;
        covariance[X3] = -1.0;
    }
};

}  // namespace fast::rf::messages::StandardMsgs
