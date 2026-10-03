#include <Infrastructure/SignalMonitor/SignalMonitor.hpp>

namespace fast::rf::core::infrastructure {
    bool SignalMonitor::newData(double timestamp) {
        if (m_startTime < 0.0) {
            m_startTime = timestamp;
        }
        m_rxCount++;

        return true;
    }
    bool SignalMonitor::update(double timestamp) {
        if (m_startTime < 0.0) {
            m_startTime = timestamp;
        }
        if (m_rxCount >= INITIAL_SAMPLES_TO_ACCUMULATE) {
            double elapTime = timestamp - m_startTime;
            m_actualRate = (double)m_rxCount / elapTime;
        }
        return true;
    }
    std::string SignalMonitor::pretty() {
        std::string str = "Signal: " + m_signalName + " Type: " + m_dataType + " RX: " + std::to_string(m_rxCount) +
                          " Rate: " + std::to_string(m_actualRate) + "(Hz) " + m_status.pretty();
        return str;
    }
}  // namespace fast::rf::core::infrastructure