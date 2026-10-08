#include <Infrastructure/SignalMonitor/SignalMonitor.hpp>
#include <cmath>
namespace fast::rf::core::infrastructure {
    bool SignalMonitor::newData(double timestamp) {
        if (m_startTime < 0.0) {
            m_startTime = timestamp;
        }
        m_rxCount++;
        fast::rf::Logger::logInfo("Signal: " + m_signalName + " Rx: " + std::to_string(m_rxCount));
        return true;
    }
    bool SignalMonitor::update(double timestamp) {
        if (m_startTime < 0.0) {
            m_startTime = timestamp;
        }
        if (m_rxCount >= INITIAL_SAMPLES_TO_ACCUMULATE) {
            double elapTime = timestamp - m_startTime;
            m_actualRateHz = (double)m_rxCount / elapTime;
        }
        // Compute Timing Diagnostic
        double percentError = 100.0 + (m_actualRateHz - m_expectedRateHz) / (m_expectedRateHz) * 100.0;
        if (percentError > m_rateTolerancePerc) {
            m_status.subSignalStatus[fast::rf::DiagnosticDefinition::DiagnosticType::TIMING].diagnosticMessage =
                fast::rf::DiagnosticDefinition::DiagnosticMessage::NOERROR;
            m_status.subSignalStatus[fast::rf::DiagnosticDefinition::DiagnosticType::TIMING].level =
                fast::rf::Level::NOERROR;
        } else {
            m_status.subSignalStatus[fast::rf::DiagnosticDefinition::DiagnosticType::TIMING].diagnosticMessage =
                fast::rf::DiagnosticDefinition::DiagnosticMessage::DIAGNOSTIC_FAILED;
            m_status.subSignalStatus[fast::rf::DiagnosticDefinition::DiagnosticType::TIMING].level =
                fast::rf::Level::WARN;
        }
        // Compute Overall Health
        fast::rf::Level level = fast::rf::Level::NOERROR;
        for (auto subSignal : m_status.subSignalStatus) {
            if (subSignal.second.level == fast::rf::Level::UNKNOWN) {
                level = fast::rf::Level::UNKNOWN;
            }
            if ((subSignal.second.level > level) && (level > fast::rf::Level::UNKNOWN)) {
                level = subSignal.second.level;
            }
        }
        m_status.level = level;
        return true;
    }
    std::string SignalMonitor::pretty() {
        std::string str = "Signal: " + m_signalName + " Type: " + m_dataType + " RX: " + std::to_string(m_rxCount) +
                          " Rate: " + std::to_string(m_actualRateHz) + "(Hz) " + m_status.pretty();
        return str;
    }
}  // namespace fast::rf::core::infrastructure