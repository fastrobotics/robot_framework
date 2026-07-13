/**
 * @file IBaseMachineSystem.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace fast::rf::BaseMachineSystem {
    /**
     * @brief Interface for the BaseMachine System
     *
     */
    class IBaseMachineSystem {
       public:
        IBaseMachineSystem() = default;
        virtual ~IBaseMachineSystem() = default;
    };
}  // namespace fast::rf::BaseMachineSystem