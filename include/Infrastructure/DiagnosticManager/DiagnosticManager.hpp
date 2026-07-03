/**
 * @file DiagnosticManager.hpp
 * @author David Gitz (davidgitz@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-07-02
 *
 * @copyright Copyright (c) 2026
 *
 */

namespace fast::rf::core::infrastructure {
    class DiagnosticManager {
       public:
        DiagnosticManager() = default;
        virtual ~DiagnosticManager() = default;

        bool init();
    };
}  // namespace fast::rf::core::infrastructure